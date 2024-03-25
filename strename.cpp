#define WIN32_LEAN_AND_MEAN
#define STRICT_GS_ENABLED
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <clocale>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <errno.h>

[[noreturn]]
void usage()
{
	fputs(
		"Alternate Data Stream Rename tool\n"
		"\n"
		"strename <file name>[:<stream name>[:$DATA]] [:]<new stream name>[:$DATA]\n"
		"strename <file name>[:<stream name>[:$DATA]] ::$DATA\n"
		"\n"
		"  file name:stream name  Specifies the data stream to rename.\n"
		"                         If no stream name is specified, the default data stream will rename.\n"
		"\n"
		"  :new stream name       Specifies a new name for the data stream.\n"
		"                         Must specify a data stream name with size 0 bytes or a data stream name that does not exist.\n"
		"                         To promote an alternate data stream to the default data stream, specify \"::$DATA\".\n",
		stderr
	);
	exit(EXIT_FAILURE);
}
[[noreturn]]
void die(const char* msg)
{
	WCHAR reason[0x400];
	if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, GetLastError(), 0, reason, ARRAYSIZE(reason), nullptr))
	{
		__fastfail(GetLastError());
	}
	else
	{
		fprintf(stderr, "%s\n%ls\n", msg, reason);
	}
	exit(EXIT_FAILURE);
}
errno_t CrtErrorCheck(errno_t error)
{
	if (error != 0 && error != STRUNCATE)
	{
		__fastfail(error);
	}
	return error;
}
int __cdecl wmain(int argc, PWSTR argv[])
{
	setlocale(LC_CTYPE, "");
	if (argc != 3)
	{
		usage();
	}

	union
	{
		FILE_RENAME_INFO file_rename_info = { .ReplaceIfExists = TRUE };
		std::byte buffer[0x400];
	};
	wcscpy(file_rename_info.FileName, L":");
	CrtErrorCheck(wcscat_s(file_rename_info.FileName, (sizeof buffer - offsetof(FILE_RENAME_INFO, FileName)) / sizeof(wchar_t), &argv[2][argv[2][0] == L':' ? 1 : 0]));
	file_rename_info.FileNameLength = static_cast<ULONG>(wcslen(file_rename_info.FileName) * sizeof(WCHAR));
	bool exceeded = false;
	const int max_path_segment_length = 255;
	if (const auto colon = wcschr(&file_rename_info.FileName[1], L':'))
	{
		exceeded = colon - &file_rename_info.FileName[1] > max_path_segment_length;
	}
	else
	{
		exceeded = wcslen(&file_rename_info.FileName[1]) > max_path_segment_length;
	}
	if (exceeded)
	{
		printf("The requested stream name length exceeds %u.\n", max_path_segment_length);
		exit(EXIT_FAILURE);
	}
	HANDLE s = CreateFileW(argv[1], DELETE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	if (s == INVALID_HANDLE_VALUE)
	{
		die("Failed to get data stream handle: ");
	}
	if (!SetFileInformationByHandle(s, FileRenameInfo, &file_rename_info, offsetof(FILE_RENAME_INFO, FileName) + file_rename_info.FileNameLength + sizeof L'\0'))
	{
		die("Failed to rename: ");
	}
}