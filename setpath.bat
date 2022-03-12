set str1="%PATH%"
if x%str1:C:\MinGW\MinGW\bin=%==x%str1% setx PATH "%PATH%;C:\MinGW\MinGW\bin"
pause