# Third Party Developer APIs Document
```
There are 3 types of APIs:
- Variables Read APIs
- Variables Write APIs
- DeBug APIs
```
### Read APIs

|Function|Type|Description|
|-|-|-|
|ifRequests()|int|To check if there is any request pending, 1 means True.|
|getPendingTime()|String|To get the FULL string of user input|
|getPendingNote()|String|**\*Under Construction\*** To get the FULL string of note input|
|getPendingCap()|int|To get the number of capsule which is under operation|
|yyGet()|int|To get the number of **_year_** input|
|mmGet()|int|To get the number of **_month_** input|
|ddGet()|int|To get the number of **_date_** input|
|hhGet()|int|To get the number of **_hour_** input|
|minGet()|int|To get the number of **_minutes_** input|

### Write APIs

|Function|Type|Usage|
|-|-|-|
|clearRequests()|void|After finish any expected movements|
|yySet(int)|void|Set the number of **_year_** |
|mmSet(int)|void|Set the number of **_month_** |
|ddSet(int)|void|Set the number of **_date_** |
|hhSet(int)|void|Set the number of **_hour_** |
|minSet(int)|void|Set the number of **_minutes_** |

### Debug APIs

|Function|Type|Description|
|-|-|-|
|clearPending()|void| Let ifRequest()=0|
