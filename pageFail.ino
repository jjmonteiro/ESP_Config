const char PAGEFAIL[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<style>
body {
  font-family: arial;  
  background-color: lightblue;
  margin: 10%;
}
h1 {
  font-size: 100px;
  text-align: center;
}
h2 {
  font-size: 20px;
}
p, a {
  font-size: 14px;
}
</style>
</head>
<body>
<h1>:(</h1>
<br>
<h2>Couldn't load default webpage!</h2>
<br>
<p>Make sure you've uploaded all 'data' folder contents into SPIFFS memory.</p>
</body>
</html>
)=====";