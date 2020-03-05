/*******************************************************************//**
 * @file    page_fail.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#ifndef page_fail_h
#define page_fail_h

const char PAGEFAIL[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<title>ESP32 Configurator</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<head>
<style>
body {
  font-family: arial;
  font-size: 16px;
  background: lightblue;
  margin: 0;
}
header {
  background-color: #333;
}
a {
  display: inline-block;
  color: white;
  padding: 14px 16px;
  text-decoration: none;
}
a:hover {
  background-color: red;
}
h1{
  font-size: 120px;
}
h3, p{
  margin-left: 10%;
}
</style>
</head>
<body>
<header>
<a href="#">Status</a>
<a href="#">Power</a>
</header>
<article>
<br>
<h1><center>:(</center></h1>
<h3>Default webpage not found.</h3>
<p>Make sure all the contents of data folder are loaded into SPIFFS memory.</p>
</article>
</body>
</html>
)=====";

#endif
/**********************************end of file**********************************/