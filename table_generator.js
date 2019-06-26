
function updateTable(tableId, dataArray){

  var tableHTML = "<tr>";
  for (var headers in dataArray[0]) {
    tableHTML += "<th>" + headers + "</th>";
  }
  tableHTML += "</tr>";
  
  for (var eachItem in dataArray) {
    tableHTML += "<tr>";
    var dataObj = dataArray[eachItem];
    for (var eachValue in dataObj){
      tableHTML += "<td>" + dataObj[eachValue] + "</td>";
    }
    tableHTML += "</tr>";
  }
  
  document.getElementById(tableId).innerHTML = tableHTML;
}
