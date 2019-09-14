
var ws;
var debug = true;
var myIP = "%IPADDR%";

var UPDATE_VALUES_INTERVAL = 10000;

function init() {
  var host;


  if (isValidIP(myIP)){
    host = "ws://" + myIP + "/ws";
  }else{
    host = "ws://localhost:81";
  }

  document.getElementById("val-host").innerHTML = host;
  ws = new WebSocket(host);


  ws.onmessage = function(e) {
    
    // e.data contains received string.
    if (e.data){
      output("reply: " + e.data);
      jsonRX(e.data);
    }
  };

  ws.onopen = function(e) {
    checkConnection();
  };
  ws.onclose = function(e) {
    checkConnection();
    stopScripts();
  };
}

function isValidIP(ipaddress) {  
  if (/^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/.test(ipaddress)) {  
    return true; 
  }   
  return false; 
}

function checkConnection(){

  var status = document.getElementById("val-status");
  var reply;


  switch (ws.readyState){
    case 0:
      reply = "connecting.."
    break;
    case 1:
      reply = "connected."
      wifiOnIcon();
      showOnly('p1');
      //updateFields();
    break;
    case 2:
      reply = "disconnecting.."
    break;
    case 3:
      reply = "disconnected."
      wifiOffIcon();
      stopScripts();
      ws.close();
      init();
    break;
    default:
      reply = "unknown status."
  }
  status.innerHTML = reply;
}

function onSend() {
  var input = document.getElementById("ter-input");
  
    if(ws.readyState!=1){
      output("> not connected!");
    }else{
      jsonTX(input.value);
    }
  
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

function readKeyboard(e) {
    if (e.which === 13) {
      onSend();
    }
    if (e.which === 27) {
      onClear();
    }
}

function toggleMenu() {
  var x = document.getElementById("navDemo");
  if (x.className.indexOf("w3-show") == -1) {
    x.className += " w3-show";//open
  } else { //close
    x.className = x.className.replace(" w3-show", "");
  }
}


function closeMenu() {
  closeSubMenu();
  var x = document.getElementById("navDemo");
  if (x.className.indexOf("w3-show") != -1) {
    x.className = x.className.replace(" w3-show", "");
  }
}

function toggleSubMenu() {
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

function closeSubMenu() {
  var x = document.getElementById("demoAcc");
  if (x.className.indexOf("w3-show") != -1) {
    x.className = x.className.replace(" w3-show", "");
    x.previousElementSibling.className = 
    x.previousElementSibling.className.replace(" w3-light-grey", "");
  }
}

function showOnly(id) {
  var x = document.getElementsByClassName("page");
  for (i = 0; i < x.length; i++) {
      document.getElementById(x[i].id).style.display = 'none';
      if (x[i].id == id){
        startScript(i+1)
      }
  }
  document.getElementById(id).style.display = 'block';
  closeMenu();
}

function startScript(id){
  stopScripts();
  switch(id){
    case 1:
      updateStatus();
      updateStatus.run = setInterval(updateStatus, UPDATE_VALUES_INTERVAL);
      break;
    case 2:
      scanWifi();
      scanWifi.run = setInterval(scanWifi, UPDATE_VALUES_INTERVAL);
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
  }
}

function stopScripts(){
  clearInterval(updateStatus.run);
  clearInterval(scanWifi.run);
}

function powerMenu(){
  
  alert("Sure to power off?");
  
  //test for icon update
  // if (x.hasAttribute("data-icon")) {
  //   x.setAttribute("data-icon", "ic:round-wifi");
  // }
  closeMenu();
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

function updateStatus(){
  jsonTX(JSON.stringify({"type":2}));
}

function scanWifi(){
  jsonTX(JSON.stringify({"type":3}));
}

function updateTable(tableId, jsonData){

  var tableHTML = "<tr>";
  for (var headers in jsonData[0]) {
    tableHTML += "<th>" + headers + "</th>";
  }
  tableHTML += "</tr>";
  
  for (var eachItem in jsonData) {
    tableHTML += "<tr>";
    var dataObj = jsonData[eachItem];
    for (var eachValue in dataObj){
      tableHTML += "<td>" + dataObj[eachValue] + "</td>";
    }
    tableHTML += "</tr>";
  }

  document.getElementById(tableId).innerHTML = tableHTML;
}

function IsJsonString(str) {
    try {
        JSON.parse(str);
    } catch (e) {
        return false;
    }
    return true;
}

function jsonTX(json_data){

  if (!json_data){return;}

  output("> " + json_data);

  if (!IsJsonString(json_data)){
    json_data = JSON.stringify({"type":0,"value":json_data})
  }

  ws.send(json_data);
}


function jsonRX(json_data){

  if (!IsJsonString(json_data)){return;}

  var obj = JSON.parse(json_data);

  switch (obj.type){
    case 0:
      //document.getElementById("text2").value = obj.value;
    break;
    case 1:
      //document.getElementById("text3").value = obj.value;
    break;
    case 2:
      updateValues(obj.value);
    break;
    case 3:
      updateTable("wifi-table", obj.value);

    break;
    default:
  }
}

function wifiOffIcon(){
  var t1 = document.getElementById("ic-wifi");
  t1.innerHTML = '<i class="iconify ic-navbar" data-icon="ic:round-wifi-off"></i>'
}

function wifiOnIcon(){
  var t1 = document.getElementById("ic-wifi");
  t1.innerHTML = '<i class="iconify ic-navbar" data-icon="ic:round-wifi"></i>'
}