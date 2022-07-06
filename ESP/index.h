const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <meta charset="UTF-8">
  <title>Monitoring Heart Rate (HeartBeat)</title>
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.1/dist/css/bootstrap.min.css"
  integrity="sha384-zCbKRCUGaJDkqS1kPbPd7TveP5iyJE0EjAuZQTgFLD2ylzuqKfdKlfG/eSrtxUkn" crossorigin="anonymous">
<script type="text/javascript" src="https://gc.kis.v2.scr.kaspersky-labs.com/FD126C42-EBFA-4E12-B309-BB3FDD723AC1/main.js?attr=o5L-bkFGq148lx49w3l9xBxQHSrAwYlhOJ2zeyyY2x0HKfP0EH9fkMUfKf_iylGOzmKa0CZEkRqaZNamm0KcaQ6nKVQ576dFcY6tE1ypB1vyValW4y0kqqK9KjFKQ4Vuo_QQk8XnXrf3ru4WtyFRue9Rnual-vUgzM_5APh5_LH59A1WdMocpkXCPoytW55-DLCYvAIx7FvGe5FmNm7lJSEpI6rcXsSggV6XOAHoynnJrh-afMOParier6hDY6zzaNRuwv7fnoyqduA0ahV4Ds18iFHxpZi4pSXaJ7SqOM8PY9RmXpMiEcDs9CY-xcBP6v0ZCc5y9KeXjCAplN-iINdv1eYamrOO6QZkvbZv4UpYcKYc1ZwU6FILaL2W4FpW" charset="UTF-8"></script></head>

<body>

  
  <div class="container">
      <div class="row item-wrap">
        <h1 style="color:#7d0633;font-family:consolas;">Temperature - Humidity Information</h1>
      
      </div>
    <div style="align-items: center; margin-left: 100px;">
      <div class="row">
      <div class="col-12 col-lg-4 item-wrap">
        <div class="flex-item">
          <p>Temperature</p>
          <canvas id="myCanvas" width="330" height="200"></canvas>
          <p>Min = 0 &nbsp;&nbsp;&nbsp; Max = 220</p>
        </div>
      </div>
      <div class="col-12 col-lg-4 item-wrap">
        <div class="flex-item">
          <p>Humidity</p>
          <canvas id="myCanvas1" width="330" height="200"></canvas>
          <p>Min = 0 &nbsp;&nbsp;&nbsp; Max = 220</p>
        </div>
      </div>
     
    </div>
    
    </div>
    </div>
    <br>
    <br>

  <style>
    html {
      font-family: Arial;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }
  
    h1 {
      font-size: 1.5rem;
    }
  
    .flex-container {
      display: flex;
      flex-direction: row;
      background-color: 0x7d0633;
      align-items: center;
      justify-content: center;
    }
  
    .item-wrap {
      justify-content: center;
      text-align: center;
    }
    .flex-item {
      /* display: inline-block; */
      background-color: white;
      padding: 20px;
      font-size: 20px;
      align-items: center;
      justify-content: center;
    }

  </style>

  <script>
    var myVar = setInterval(myTimer, 1000); //--> Create a loop to send a request to NodeMCU to get the BPM value every 1 second.
    var getHR = 0; //--> Variable to get the BPM value from NodeMCU.
    var getSYS = 0; //--> Variable to get the SYS value from NodeMCU.

    function myTimer() {
      getHeartRateVal();
      getSYSPressureVal();
      getDIAPressureVal();
    }

    //------------------------------------------------------------Function for sending request to NodeMCU to get BPM value.
    function getHeartRateVal() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          getHR = this.responseText;
        }
      };
      xhttp.open("GET", "gettemperature", true);
      xhttp.send();
    }
    //------------------------------------------------------------


    //------------------------------------------------------------Function for sending request to NodeMCU to get SYS value.
    function getSYSPressureVal(){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange =function(){
        if(this.readyState == 4 && this.status == 200){
          getSYS = this.responseText;
          
        }
      };
      xhttp.open("GET", "getSYSPressure", true);
      xhttp.send();
    }
    //------------------------------------------------------------




    //------------------------------------------------------------Display the BPM value and create a circle progress bar.
    var canvas = document.getElementById('myCanvas');
    var context = canvas.getContext('2d');
    var start = 1.58;
    var cw = context.canvas.width / 2;
    var ch = context.canvas.height / 2;
    var diff;

    var cnt = 0;
    var bar = setInterval(progressBar, 10);
    function progressBar() {
      var HR = map(getHR, 0, 220, 0, 100);
      diff = (cnt / 100) * Math.PI * 2;
      context.clearRect(-100, 0, 400, 200);
      context.beginPath();
      context.arc(cw, ch, 70, 0, 2 * Math.PI, false);
      context.fillStyle = '#FFF';
      context.fill();
      context.strokeStyle = '#e7f2ba';
      if(getHR <=49 || getHR >= 130){
        context.strokeStyle = '#fa8072';
      }
      context.stroke();
      context.fillStyle = '#000';
      context.strokeStyle = '#b3cf3c';
      context.textAlign = 'center';
      if(getHR <= 49 || getHR >= 130){
        context.strokeStyle = '#ff0000';
        context.textAlign = 'center';
      }
      context.lineWidth = 15;
      context.font = '15pt Verdana';
      context.beginPath();
      context.arc(cw, ch, 70, start, diff + start, false);
      context.stroke();
      context.fillText(getHR + ' oC', cw + 2, ch + 6);

      if (cnt < HR) {
        cnt++;
      }

      if (cnt > HR) {
        cnt--;
      }
    }
    //------------------------------------------------------------

    //------------------------------------------------------------Display the SYS value and create a circle progress bar.
    var canvas1 = document.getElementById('myCanvas1');
    var context1 = canvas1.getContext('2d');
    var start1 = 1.58;
    var cw1 = context1.canvas.width / 2;
    var ch1 = context1.canvas.height / 2;
    var diff1;

    var cnt1 = 0;
    var bar1 = setInterval(progressBar1, 10);
    function progressBar1() {
      var SYS = map(getSYS  , 0, 220, 0, 100);
      diff1 = (cnt1 / 100) * Math.PI * 2;
      context1.clearRect(0, 0, 400, 200);
      context1.beginPath();
      context1.arc(cw, ch, 70, 0, 2 * Math.PI, false);
      context1.fillStyle = '#FFF';
      context1.fill();
      context1.strokeStyle = '#e7f2ba';
      if(getSYS <=49 || getSYS >= 180){
        context.strokeStyle = '#fa8072';
      }
      context1.stroke();
      context1.fillStyle = '#000';
      context1.strokeStyle = '#b3cf3c';
      context1.textAlign = 'center';
      if(getSYS <= 49 || getSYS >= 180){
        context.strokeStyle = '#ff0000';
        context.textAlign = 'center';
      }
      context1.lineWidth = 15;
      context1.font = '15pt Verdana';
      context1.beginPath();
      context1.arc(cw1, ch1, 70, start1, diff1 + start1, false);
      context1.stroke();
      context1.fillText(getSYS + ' %', cw1 + 2, ch1 + 6);

      if (cnt1 < SYS) {
        cnt1++;
      }

      if (cnt1 > SYS) {
        cnt1--;
      }
    }
    

    //------------------------------------------------------------Scale from the BPM value to the Progress bar value.
    // The BPM value is min = 0 and max = 220 is scaled to the Progress bar value min = 0 and max = 100.
    function map(x, in_min, in_max, out_min, out_max) {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    //------------------------------------------------------------
  </script>
</body>
</html>
)=====";
