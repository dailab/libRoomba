#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <unistd.h>

#include "libroomba.h"

using namespace ssr;
using namespace std;

void
printStatus(Roomba* r, uint timeout_us=ROOMBA_INFINITE){
	auto temp = r->getTemperature(timeout_us);
	cout << "Temperature: " << (int) temp << endl;
	auto volt = r->getVoltage(timeout_us);
	cout << "Voltage: " << (int) volt << endl;
	auto current = r->getCurrent(timeout_us);
	cout << "Current: " << (int) current << endl;
	auto s = r->getChargingState(timeout_us);
	cout << "ChargingState: " << s << endl;
	auto v = r->getCurrentVelocity();
	cout << "Velocity: " << v.x << "/" << v.y << "/" << v.th << endl;
	auto dist = r->getDistance(timeout_us);
	cout << "Distance=" << dist << endl;
	auto angle = r->getAngle(timeout_us);
	cout << "Angle=" << angle << endl;
	auto home = r->isHome();
	cout << "Home=" << home << endl;
}

int main(const int argc, const char* argv[]) {
  int baudrate = 115200;
  if(argc == 1) {
    std::cout << "USAGE: demo /dev/ttyUSB0" << std::endl;
    std::cout << "Press enter key to exit" << std::endl;
    getchar();
    return 0;
  } else if (argc == 3) {
    baudrate = atoi(argv[2]);
  }
	
	Roomba* pRoomba = nullptr;
  try {
    pRoomba = createRoomba(MODEL_500SERIES, argv[1], baudrate);
		pRoomba->start();
cout << "* 1" << endl;
    pRoomba->safeControl();
    //pRoomba->runAsync();

		Mode mode;

#if 1
cout << "* 2" << endl;
		printStatus(pRoomba, 2000 * 1000);
cout << "* 3" << endl;
		
		mode = pRoomba->getMode();
		std::cout << "Mode=" << mode << std::endl;
#endif

#if 0
		pRoomba->fullControl();
		pRoomba->driveSideBrush(MOTOR_CW);
		sleep(1);
		pRoomba->driveSideBrush(MOTOR_OFF);
		sleep(1);
		pRoomba->driveSideBrush(MOTOR_CCW);
		sleep(1);
		pRoomba->driveSideBrush(MOTOR_OFF);
#else
		int16_t dist;
		int16_t angle;

#if 0
cout << "#1" << endl;
		for(int i=0; i<5; i++){
			dist = pRoomba->getDistance();
			cout << "dist=" << dist << endl;
		}
#endif
		
#if 0
		pRoomba->drive(100, 0);
		sleep(1);
		pRoomba->drive(0,0);
		sleep(1);

cout << "#2" << endl;
		dist = pRoomba->getDistance();
		cout << "dist=" << dist << endl;

		pRoomba->drive(-100, 0);
		sleep(1);
		pRoomba->drive(0,0);
		sleep(1);
	
cout << "#3" << endl;
		dist = pRoomba->getDistance();
		cout << "dist=" << dist << endl;
		//cout << "dist=" << dist << endl;

		sleep(1);
cout << "#4" << endl;
		dist = pRoomba->getDistance();
		//cout << "dist=" << dist << endl;
		cout << "dist=" << dist << endl;

		mode = pRoomba->getMode();
		std::cout << "Mode=" << mode << std::endl;

cout << "#5" << endl;
		angle = pRoomba->getAngle();
		cout << "angle=" << angle << endl;

		pRoomba->drive(150, 1);
		sleep(1);
		pRoomba->drive(0, 0);
		usleep(200000);
cout << "#6" << endl;
		angle = pRoomba->getAngle();
		cout << "angle=" << angle << endl;

		pRoomba->drive(150, -1);
		sleep(1);
		pRoomba->drive(0, 0);
		usleep(200000);
cout << "#7" << endl;
#endif

#if 1
		try{
			angle = pRoomba->getAngle();
			cout << "angle=" << angle << endl;
			pRoomba->turn(90, 50);
			sleep(1);
			pRoomba->turn(-90, 50);
			sleep(1);
			printStatus(pRoomba, 5000 * 1000);
		} catch(TimeoutException& e){
			cerr << "got timeout exception" << endl;
		}
#endif

		
#if 0 // test current
		int16_t current;
		current = pRoomba->getSideBrushMotorCurrent();
		cout << "current=" << current << endl;
		pRoomba->driveSideBrush(MOTOR_CW);
		sleep(1);
		current = pRoomba->getSideBrushMotorCurrent();
		cout << "current=" << current << endl;
		pRoomba->driveSideBrush(MOTOR_OFF);
		current = pRoomba->getSideBrushMotorCurrent();
		sleep(1);
		cout << "current=" << current << endl;
#endif

#if 0 // test status in different modes
		
		cout << "---- safe mode ----" << endl;
		printStatus(pRoomba);
		pRoomba->spotClean();
		sleep(5);
		cout << "---- spot cleaning mode ----" << endl;
		printStatus(pRoomba);
    pRoomba->safeControl();
		sleep(2);
		cout << "---- safe mode ----" << endl;
		printStatus(pRoomba);
#endif
	

#if 0
		try{
			pRoomba->driveSideBrush(MOTOR_CW);
			pRoomba->move(500, 100);
			pRoomba->turn(-90, 50);
			pRoomba->move(200, 50);
			pRoomba->move(-200, 50);
			pRoomba->turn(-90, 100);
			pRoomba->move(500, 50);
			pRoomba->turn(180, 100);
			pRoomba->driveSideBrush(MOTOR_OFF);
		} catch(TimeoutException& e){
			cerr << "got timeout exception" << endl;
		}
#endif

		//sleep(1);
		//cout << "starting dock mode..." << endl;
		//pRoomba->dock();
		//mode = pRoomba->getMode();
		//std::cout << "Mode=" << mode << std::endl;

#if 0
		cout << "starting spot clean mode..." << endl;
		pRoomba->spotClean();

		do{
			sleep(1);
			mode = pRoomba->getMode();
			std::cout << "Mode=" << mode << std::endl;
			printStatus(pRoomba);
		}while(true);
#endif

#endif

		mode = pRoomba->getMode();
		std::cout << "Mode=" << mode << std::endl;

    int c;
    //std::cin >> c;
    //pRoomba->clean();

    //pRoomba->safeControl();
    //std::cin >> c;
		//sleep(30);
		cout << "done." << endl;
    delete pRoomba;
  } catch (std::exception &e) {
    std::cout << "Excepiton:" << e.what() << std::endl;
		if(pRoomba){
    	pRoomba->safeControl(); // TODO: -> powerDown
			delete pRoomba;
		}
  }

  int c;
  //std::cin >> c;
  return 0;
}
