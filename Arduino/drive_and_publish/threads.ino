


void tickcallback()
{
  // Serial.println("Number of Ticks: ");
  // Serial.println(right_wheel_tick_count);
  // Serial.println(left_wheel_tick_count);
  // Serial.println();
  leftPub.publish( &left_wheel_tick_count );
  rightPub.publish( &right_wheel_tick_count );
  nh.spinOnce();
 
  // Calculate the velocity of the right and left wheels
  //calc_vel_right_wheel();
  //calc_vel_left_wheel()
}
    