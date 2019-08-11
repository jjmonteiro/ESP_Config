
var ws;
var debug = true;
var myIP = "%IPADDR%";

function init() {
  var timer1 = setInterval(checkConnection, 5000);

  if (isValidIP(myIP)){
    ws = new WebSocket("ws://" + myIP + "/ws");
  }else{
    ws = new WebSocket("ws://localhost:81");
  }
  
  ws.onmessage = function(e) {
    
    // e.data contains received string.
    if (e.data){
      
      jsonRX(e.data);
    }
  };

  ws.onopen = function(e) {
    
    //checkConnection();
  };
  ws.onclose = function(e) {
    //clearInterval(timer1);
    //checkConnection();
  };
}

function isValidIP(ipaddress) {  
  if (/^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/.test(ipaddress)) {  
    return true; 
  }   
  return false; 
}  

function updateFields(){
  jsonTX(JSON.stringify({"type":0,"value":"ping"}));
}

function checkConnection(){

  var reply;

  switch (ws.readyState){
    case 0:
      reply = "Connecting.."
    break;
    case 1:
      reply = "Connected."
      //updateFields();
    break;
    case 2:
      reply = "Disconnecting.."
    break;
    case 3:
      reply = "Disconnected."
        ws.close();

        init();
    break;
    default:
      reply = "Unknown Status."
  }
  //just for debug, this function will later update an icon
  //output(reply);
}

function onSend() {
  var input = document.getElementById("ter-input");
  

  if(ws.readyState!=1){
    output("not connected!");
    return;
  }

  jsonTX(input.value);
  input.value = "";
}


function onClear() {
  var log = document.getElementById("ter-main");
  log.innerHTML = "";
}

function output(str) {
  var log = document.getElementById("ter-main");
  //var escaped = str.replace(/&/, "&amp;").replace(/</, "&lt;").
  //replace(/>/, "&gt;").replace(/"/, "&quot;"); // "
  log.innerHTML += str + '\n';
  log.scrollTop = log.scrollHeight;
}


function toggleGrey(elementid){
  var status = document.getElementById(elementid);
  status.disabled = !status.disabled;
}

function runScript(e) {
    if (e.which === 13) {
      onSend();
    }
    if (e.which === 27) {
      onClear();
    }
}

function myFunction() {
  var x = document.getElementById("navDemo");
  if (x.className.indexOf("w3-show") == -1) {
    x.className += " w3-show";
  } else { 
    x.className = x.className.replace(" w3-show", "");
  }
}

function myAccFunc() {
  var x = document.getElementById("demoAcc");
  if (x.className.indexOf("w3-show") == -1) {
    x.className += " w3-show";
    x.previousElementSibling.className += " w3-light-grey";
  } else { 
    x.className = x.className.replace(" w3-show", "");
    x.previousElementSibling.className = 
    x.previousElementSibling.className.replace(" w3-light-grey", "");
  }
}


function showOnly(id) {
  var x = document.getElementsByClassName("page");
  for (i = 0; i < x.length; i++) {
      document.getElementById(x[i].id).style.display = 'none';
  }
  document.getElementById(id).style.display = 'block';
}

function powerMenu(){

  alert("Sure to power off?");
}


function updateValues(dataValues){
  myObj = dataValues[0];
  for (key in myObj) {
    var value = myObj[key]+"%";
    var elem = document.getElementById("bar-"+key);
    elem.style.width = value;
    var elem = document.getElementById("val-"+key);
    elem.innerHTML = value;
  }
}