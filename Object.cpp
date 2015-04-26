// Class Object
// can be used to create AI sprites as well
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include "Object.h"

Object::Object( double w, double h, double x, double y ) {
    width  = w;
    height = h;
    center.x = x;
    center.y = y;
    center.z = 0;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	camera.x = 0;
	camera.y = 0;
	camera.z = 0;
    windowCenter = 300;
    interval = 50;
}
void Object::setWidth( double w ) {
    width = w;
}
double Object::getWidth( void ) {
    return width;
}
void Object::setHeight( double h ) {
    height = h;
}
double Object::getHeight( void ) {
    return height;
}
void Object::setCenter( double x, double y ) {
    center.x = x;
    center.y = y;
    center.z = 0;
}
double Object::getCenterX( void ) {
    return center.x;
}
double Object::getCenterY( void ) {
    return center.y;
}
double Object::getVelocityX( void ) {
    return velocity.x;
}
double Object::getVelocityY( void ) {
    return velocity.y;
}
double Object::getCameraX( void ) {
    return camera.x;
}
double Object::getCameraY( void ) {
    return camera.y;
}
void Object::setVelocityX( double x ) {
    velocity.x = x;
}
void Object::setVelocityY( double y ) {
    velocity.y = y;
}
void Object::setCameraX( double x ) {
    camera.x = x;
}
void Object::setCameraY( double y ) {
    camera.y = y;
}


double Object::getOldCenterX(void){
  return oldCenter.x;
}
double Object::getOldCenterY(void){
  return oldCenter.y;
}
void Object::setOldCenter(void){
  oldCenter.x = center.x;
  oldCenter.y = center.y;
  oldCenter.z = 0;
}

double Object::getTop(){
  return center.y + height;
}
double Object::getBottom(){
  return center.y - height;
}
double Object::getRight(){
  return center.x + width;
}
double Object::getLeft(){
  return center.x - width;
}

double Object::getOldTop(){
  return oldCenter.y + height;
}
double Object::getOldBottom(){
  return oldCenter.y - height;
}
double Object::getOldRight(){
  return oldCenter.x + width;
}
double Object::getOldLeft(){
  return oldCenter.x - width;
}


// screen boundaries for scrolling
double Object::getWindowCenter(){
  return windowCenter;
}
void Object::scrollWindow(double amount){
  windowCenter += amount;
}
double Object::getWindowInterval() {
    return interval;
}
