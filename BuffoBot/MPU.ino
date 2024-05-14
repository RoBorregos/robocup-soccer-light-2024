float filter(float input) {
  // Almacenar la muestra actual en el arreglo
  samples[sampleIndex] = input;

  // Incrementar el índice de muestra
  sampleIndex = (sampleIndex + 1) % numSamples;

  // Aplicar el filtro
  float filteredValue = b0 * input + b1 * samples[(sampleIndex - 1 + numSamples) % numSamples] + b2 * samples[(sampleIndex - 2 + numSamples) % numSamples]
                      - a1 * samples[(sampleIndex - 1 + numSamples) % numSamples] - a2 * samples[(sampleIndex - 2 + numSamples) % numSamples];

  return filteredValue;
}

void gyroValues(int16_t *gyro, int16_t *accel, int32_t *quat) {
    // Calcular ángulos de movimiento:
    Quaternion q;
    VectorFloat gravity;
    float ypr[3] = {0, 0, 0};
    float xyz[3] = {0, 0, 0};
    mpu.GetQuaternion(&q, quat);
    mpu.GetGravity(&gravity, &q);
    mpu.GetYawPitchRoll(ypr, &q, &gravity);
    mpu.ConvertToDegrees(ypr, xyz);
    double angle = xyz[0];
    double filtered_angle = filter(angle); 
    yaw = filtered_angle;
    
    yaw = -yaw; 
    
    //Serial.println(filtered_angle);
}

double actualizeMPU () {
  static unsigned long FIFO_DelayTimer;
  if ((millis() - FIFO_DelayTimer) >= (99)) {
      if (mpu.dmp_read_fifo(false)) FIFO_DelayTimer = millis();
  }
}