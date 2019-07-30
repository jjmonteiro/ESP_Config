
function updateTable(tableId, jsonData){

  var tableHTML = "<thead><tr class='w3-black'>";
  for (var headers in jsonData[0]) {
    tableHTML += "<th>" + headers + "</th>";
  }
  tableHTML += "</tr></thead>";
  
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
