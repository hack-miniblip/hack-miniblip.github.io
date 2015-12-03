Miniblip Library

Some ideas of @victordiaz

  miniblip.beep(note,  duration)
  miniblip.matrix(i, j, r, g, b);
  miniblip.matrixBrightness([0 ... 100);
  miniblip.readButton();
  miniblip.readPot();
  miniblip.save(position, value); //Use the internal limited eeprom
  miniblip.load(position, value); //load the stored value

   //this is for the "circles".
  //Since the capacitance changes depending on the environment or things connected we need a way to calibrate them on the fly.
  miniblip.setCapacitivePin([ pin number], );
  miniblip.capacitivePinThreeshold(value)
