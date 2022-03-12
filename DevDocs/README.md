# Third Party Developer APIs Document
```
There are 3 types of APIs:
- Variables Read APIs
- Variables Write APIs
- DeBug APIs
```
### Read APIs

|Function|Function Type|Description|
|-|-|-|
|ifRequests()|int|To check if there is any request pending, 1 means True.|
|getPendingTime()|String|To get the FULL string of user input **while _inserting info_**.|
|getPendingNote()|String|**\*Under Construction\*** To get the FULL string of note input|
|getPendingCap()|int|To get the number of capsule which is under operation|
|yyGet()|int|To get the number of **_year_** input in **"Time Set"** period.|
|mmGet()|int|To get the number of **_month_** input in **"Time Set"** period.|
|ddGet()|int|To get the number of **_date_** input in **"Time Set"** period.|
|hhGet()|int|To get the number of **_hour_** input in **"Time Set"** period.|
|minGet()|int|To get the number of **_minutes_** input in **"Time Set"** period.|

### Write APIs

|Function|Request Parameter|Restriction|Usage|
|-|-|-|-|
|clearRequests()| - | - |After finish any expected movements|
|yySet(int)|int,1|Yes|Set the number of **_year_** |
|mmSet(int)|int,1|Yes|Set the number of **_month_** |
|ddSet(int)|int,1|Yes|Set the number of **_date_** |
|hhSet(int)|int,1|Yes|Set the number of **_hour_** |
|minSet(int)|int,1|Yes|Set the number of **_minutes_** |

### Debug APIs

|Function|Type|Description|
|-|-|-|
|clearPending()|void| Let ifRequest()=0|

### Basic Functions
|Function|Request Parameter|Restriction|Description|
|-|-|-|-|
|HTMLsetup()|int,1|No, Default is 0|Send 1 to start Serial debug|
|HTTPLoop()|int,1|No, Default is 0|Send 1 to start Serial debug|
