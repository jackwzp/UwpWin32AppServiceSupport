# UWP App and WinForm AppService Communication Support

This repo is a sample code base to illustrate some problems we have with AppService communication. This sample app is not our real app but serve as a demonstration of the issue we're having. Not all the problems we have in the real app can be reproduced in this sample but it shows the key pieces of code for the AppService.

## Summary

There are two separate issue we noticed:

- The data exchange with AppService just stops after roughly a minute. The sender (UWP app) keeps sending data but the consumer (WinForm app) no longer receiving data. This is NOT reproducible in this sample app.

- There seems to be a memory leak issue going on. The memory profiler in VisualStudio2015 show the memory slowly increasing over time but the system doesn't seem to be freeing up memory at all. This is reproducible in this sample app.


## Drop Data Problem

This first problem is a show stopper for us as we can not guarantee the reliablity of data transmission. It seems like this problem is only happening in Release Mode configuration but works fine in Debug. The Output Window seems to show 2 different messages when the data drop.

- In one case, the following exception is being thrown repeateadly, which seems to correspondes to the SendMessage() call from UWP to WinForm.

```
Exception thrown at 0x00007FFADE563C58 in MuseDirect.exe: Microsoft C++ exception: wil::ResultException at memory location 0x000000FD546FDC70.
Exception thrown at 0x00007FFADE563C58 in MuseDirect.exe: Microsoft C++ exception: [rethrow] at memory location 0x0000000000000000.
....continuously repeats...
```

- In another case, the following exceptiong is being thrown a few times and then the data transmission drops.
```
Exception thrown at 0x00007FFADE563C58 (KernelBase.dll) in MuseDirect.exe: 0x000006D9: There are no more endpoints available from the endpoint mapper.
```

I'm doing debug prints in the sender (UWP app) and the receiver (WinForm app). In both cases, the sender seem to keep sending data. I see the debug print lines in the Output window but the actually SendMessageAsync() call might not be doing anything. Hence, that's why I'm not seeing the receiver's print lines in the Output window.

## Memory leak problem

The second problem which is reproducible in this sample code is memory leak. The memory profiler of the UWP app shows the memory usage increasing at a steady rate (although slowly) but never frees anything. I'm not sure what could be the cause of this since I'm not creating any new objects for every message.

## Project configuration

We try running this in both Debug and Release mode. The data drop issue seem to only happen in Release mode and not in Debug. The memory leak issue happens in both Debug and Release.


