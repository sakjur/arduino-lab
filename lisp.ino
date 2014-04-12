char input[120];
int on_board_led = 13;

int parse_line(char * data);

void setup() { 
  pinMode(on_board_led, OUTPUT);
  Serial.begin(9600);
  while (!Serial)
  {
    digitalWrite(on_board_led, HIGH);
    delay(100);
    digitalWrite(on_board_led, LOW);
    delay(100);
  }
  Serial.println("lispy 0.1");
}

void loop() {
  int char_count = 0;

  Serial.print("%> ");
  while(char_count < 120)
    if (Serial.available() > 0)
    {
      char incoming_data = Serial.read();
      Serial.print(incoming_data);
      
      if (incoming_data == 0xA) // New Line
        break;
        
      input[char_count] = incoming_data;
      char_count = char_count + 1;
      
      // Next byte is set to NIL to prevent from keeping old data.
      input[char_count] = '\0';
    }
  Serial.println(parse_line(input));
}

int parse_line(char * data) {
   int a = 0;
   int b = 0;

   if (data[2] >= '0' && data[2] <= '9')
     a = data[2] - '0';
   if (data[4] >= '0' && data[4] <= '9')
     b = data[4] - '0';
   
  
  if (data[0] == '+')
    return a + b;
  else if (data[0] == '-')
    return a - b;
  else if (data[0] == '*')
    return a * b;
  else if (data[0] == '/')
    return a / b;
}
