// Variables
var ws = undefined; // websocket instance
var logs = [];
var logsLimit = 4;
var b = document.getElementById('btnWS');
// Initialize the WebSocket
function initWebSocket() {
    //    var ipName = "192.168.43.78";
    var ipName = window.location.hostname;
    if (ws) {
        ws.close(); // close the websocket if open.
        ws = undefined;
    }
    ws = new WebSocket('ws://' + ipName + '/stream');
    ws.onopen = function () { // when handshake is complete:
        log('WebSocket open to ZentriOS device ' + ipName);
        //*** Change the text of the button to read "Stop Webcam" ***//
        var elem = document.querySelector("#btnWS");
        elem.textContent = "Stop Webcam";
        elem.title = "Click to stop webcam";
        elem.disabled = false;
        //*** Change the title attribute of the button to display "Click to stop webcam" ***//
        //*** Enable the button" ***//
    };
    ws.onclose = function () { // when socket is closed:
        log('WebSocket connection to ' + ipName + ' has been closed!');
        //*** Change the text of the button to read "Start Webcam" ***//
        var el = document.querySelector("#btnWS");
        el.textContent = "Start Webcam";
        el.title = "Click to start webcam";
        el.disabled = false;
        //*** Change the title attribute of the button to display "Click to start webcam" ***//
        //*** Enable the button" ***//
    };
    ws.onmessage = function (event) {
        var date = new Date();
        var month = date.getMonth() + 1;
        var day = date.getDate();
        var hour = date.getHours();
        var min = date.getMinutes();
        var sec = date.getSeconds();
        month = (month < 10 ? "0" : "") + month;
        day = (day < 10 ? "0" : "") + day;
        hour = (hour < 10 ? "0" : "") + hour;
        var s = "AM";
        if (hour >= 12) var s = "PM";
        if (hour > 12) hour = hour - 12;
        min = (min < 10 ? "0" : "") + min;
        sec = (sec < 10 ? "0" : "") + sec;
        var str = hour + ":" + min + ":" + sec + s + "  " + month + "/" + day + "/" + date.getFullYear();
        document.querySelector("#time").textContent = str;
        // when client receives a WebSocket message:
        //*** Display a new timestamp ***//
        document.querySelector("#pic").src = "../img.jpg";
        //*** Set the source of the image to the image on the WiFi chip ***//
    };
    ws.onerror = function () { // when an error occurs
        ws.close();
        log('Websocket error');
        var el = document.querySelector("#btnWS");
        el.textContent = "Start Webcam";
        el.title = "Click to start webcam";
    };
}
// Set up event listeners
var btn = document.querySelector("#btnWS");
btn.onclick = function () {
    var ele = document.querySelector("#btnWS");
    ele.disabled = true;
    if (ele.textContent == "Start Webcam") {
        initWebSocket();
    }
    else if (ele.textContent == "Stop Webcam") {
        
        ws.close();
    }
};
//*** When the button is clicked, disable it, and depending on whether a Websocket is open or not, either run "initWebSocket()" or "ws.close()" ***//
// Other functions
function log(txt) {
    logs.push({
        'content': txt
        , 'type': 'log'
    });
    showLog(logs, 'log', logsLimit);
}

function showLog(logArray, logId, logLimit) {
    var logContent = '';
    var logLength = logArray.length;
    var iStart = logLength - logLimit - 1;
    if (iStart < 0) {
        iStart = 0;
    }
    for (var index = iStart; index < logLength; ++index) {
        logItem = logArray[index];
        logContent += '<span class="' + logItem.type + '">' + logItem.content + '</span><br/>\n'
    }
    document.getElementById(logId).innerHTML = logContent;
}
// Define initialization function
function init() {
    initWebSocket();
}
// Open Websocket as soon as page loads
window.addEventListener("load", init, false);