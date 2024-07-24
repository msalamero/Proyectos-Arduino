5.	#include <Arduino.h>
6.	#include <AFMotor.h>
7.	#include <Servo.h>
8.	
9.	AF_DCMotor motor1(1);
10.	AF_DCMotor motor2(2);
11.	AF_DCMotor motor4(4);
12.	Servo myServo;
13.	
14.	String command = "";
15.	unsigned long lastPingTime = 0;
16.	void resetBluetooth();
17.	void handleCommand(String cmd);
18.	void processSingleCommand(String cmd);
19.	void processCombinedCommand(String cmd);
20.	
21.	void setup() {
22.	
23.	Serial.begin(9600);
24.	myServo.attach(10);
25.	motor1.setSpeed(255);
26.	motor2.setSpeed(255);
27.	motor4.setSpeed(255);
28.	
29.	lastPingTime = millis();
30.	}
31.	
32.	void loop() {
33.	while (Serial.available()) {
34.	char c = (char)Serial.read();
35.	if (c == '\n') {
36.	handleCommand(command);
37.	command = "";
38.	} else {
39.	command += c;
40.	}
41.	}
42.	if (millis() - lastPingTime > 15000) {
43.	resetBluetooth();
44.	}
45.	}
46.	
47.	void handleCommand(String cmd) {
48.	lastPingTime = millis();
49.	
50.	if (cmd.startsWith("PING")) {
51.	Serial.println("PONG");
52.	} else if (cmd.indexOf('-') != -1) {
53.	processCombinedCommand(cmd);
54.	} else {
55.	processSingleCommand(cmd);
56.	}
57.	
58.	void processSingleCommand(String cmd) {
59.	if (cmd.startsWith("FWD")) {
60.	int speed = cmd.substring(3).toInt();
61.	motor1.setSpeed(speed);
62.	motor2.setSpeed(speed);
63.	motor1.run(FORWARD);
64.	motor2.run(FORWARD);
65.	} else if (cmd.startsWith("BCK")) {
66.	int speed = cmd.substring(3).toInt();
67.	motor1.setSpeed(speed);
68.	motor2.setSpeed(speed);
69.	motor1.run(BACKWARD);
70.	motor2.run(BACKWARD);
71.	} else if (cmd.startsWith("LFT")) { /
72.	int speed = cmd.substring(3).toInt();
73.	motor1.setSpeed(speed);
74.	motor2.setSpeed(speed);
75.	motor1.run(FORWARD);
76.	motor2.run(BACKWARD);
77.	} else if (cmd.startsWith("RGT")) {
78.	int speed = cmd.substring(3).toInt();
79.	motor1.setSpeed(speed);
80.	motor2.setSpeed(speed);
81.	motor1.run(BACKWARD);
82.	motor2.run(FORWARD);
83.	} else if (cmd == "STP") {
84.	motor1.run(RELEASE);
85.	motor2.run(RELEASE);
86.	} else if (cmd == "BMP") {
87.	motor4.run(FORWARD);
88.	} else if (cmd == "STB") {
89.	motor4.run(RELEASE);
90.	} else if (cmd.startsWith("SRV")) {
91.	int angle = cmd.substring(3).toInt();
92.	myServo.write(angle);
93.	} else {
94.	
95.	}
96.	}
97.	
98.	void processCombinedCommand(String cmd) {
99.	int separatorIndex = cmd.indexOf('-');
100.	String firstPart = cmd.substring(0, separatorIndex);
101.	String secondPart = cmd.substring(separatorIndex + 1);
102.	
103.	processSingleCommand(firstPart);
104.	processSingleCommand(secondPart);
105.	}
106.	
107.	void resetBluetooth() {
108.	motor1.run(RELEASE);
109.	motor2.run(RELEASE);
110.	motor4.run(RELEASE);
111.	myServo.write(90);
112.	Serial.println("Desconectando por inactividad...");
113.	}
114.	
