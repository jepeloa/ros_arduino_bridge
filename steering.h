int steering_angle_value=0;  //variable que almacena el angulo de la direccion
void steering_angle (){        //funcion que calcula la conversion del angulo
  int dir_pos;
// Serial.println(steering_angle_value);
  dir_pos=analogRead(1);
 // Serial.println(dir_pos);
 if (steering_angle_value> MAX_ENCODER_VALUE) {  //si el valor es mayor a este argumento estoy con el servo totalmente retraido
      digitalWrite(5,LOW);
      return;
      }  
      if (steering_angle_value< MIN_ENCODER_VALUE) {  //si el valor es mayor a este argumento estoy con el servo totalmente retraido
      digitalWrite(5,LOW);
      return;
      }
 if (steering_angle_value < dir_pos) {   //si el valor del argumento es menor al de la posicion el servo debe retraerse
      digitalWrite(4,LOW);
      delay(1);
      digitalWrite(5,HIGH);  
      }

 else if(steering_angle_value > dir_pos+5) {                     //agrego un gap para que no se solape permanentemente lo mismo que el caso anterior pero invirtiendo los estados logicos, el servo debe extenderse
      digitalWrite(4,HIGH);
      delay(1);
      digitalWrite(5,HIGH);    
      }
 else {
       digitalWrite(5,LOW); 
 }
       
}
void update_steering() {
 if (!moving){
    digitalWrite(5,LOW);
    return;
  }

else{

  steering_angle();
}
  }
