
```
Alternate Data Stream Rename tool

strename <file name>[:<stream name>[:$DATA]] [:]<new stream name>[:$DATA]
strename <file name>[:<stream name>[:$DATA]] ::$DATA

  file name:stream name  Specifies the data stream to rename.
                         If no stream name is specified, the default data stream will rename.

  :new stream name       Specifies a new name for the data stream.
                         Must specify a data stream name with size 0 bytes or a data stream name that does not exist.
                         To promote an alternate data stream to the default data stream, specify "::$DATA".
```
### Reference
- [FILE_RENAME_INFORMATION structure (ntifs.h)](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/ns-ntifs-_file_rename_information#:~:text=special%20rules%20for%20renaming%20ntfs%20data%20streams)  
Rules for renaming data streams is here.
- [[MS-FSCC]: Appendix B: Product Behavior](https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-fscc/d4bc551b-7aaf-4b4f-ba0e-3a75e7c528f0#:~:text=refs%20does%20not%20support%20renaming%20of%20alternate%20data%20streams.)  
There is one exception.

###### LICENSE
MIT License

