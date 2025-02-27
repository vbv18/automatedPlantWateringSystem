int water;
int ultraSonic = 0;
int relay = 2;
int soilSensor = 3;
int trigger = 4;
int echo = 5;
int a = 6, b = 7, c = 8, d = 9, e = 10, f = 11, g = 12;

void setup()
{
    Serial.begin(9600);
    pinMode(relay, OUTPUT);
    pinMode(soilSensor, INPUT);
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
    digitalWrite(relay, LOW);
    resetDisplay();
}

void resetDisplay()
{
    // Turn off all segments
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
}

void displayDigit(int dig)
{
    // Reset the display
    resetDisplay();

    // Turn on segments for the given digit
    switch (dig)
    {
    case 0:
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        break;
    case 1:
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        break;
    case 2:
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(g, HIGH);
        break;
    case 3:
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(g, HIGH);
        break;
    case 4:
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        break;
    case 5:
        digitalWrite(a, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        break;
    }
}

long readUltrasonicDistance(int trigger, int echo)
{
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    long duration = pulseIn(echo, HIGH, 30000);
    if (duration == 0)
    {
        return -1;
    }
    return (duration * 0.034 / 2);
}

void loop()
{

    water = digitalRead(soilSensor);

    if (water == LOW)
    {
        digitalWrite(relay, HIGH);
    }
    else
    {
        digitalWrite(relay, LOW);
    }

    long distance = readUltrasonicDistance(trigger, echo);
    ultraSonic = (int)distance;
    Serial.print("Distance: ");
    Serial.println(ultraSonic);

    if (ultraSonic > 40)
    {
        displayDigit(0);
    }
    else if (ultraSonic > 30)
    {
        displayDigit(1);
    }
    else if (ultraSonic > 20)
    {
        displayDigit(2);
    }
    else if (ultraSonic > 10)
    {
        displayDigit(3);
    }
    else if (ultraSonic > 5)
    {
        displayDigit(4);
    }
    else
    {
        displayDigit(5);
    }

    delay(3000);
}
