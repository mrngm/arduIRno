char* params;
if (params = e.serviceRequest())
{
  e.print("<H1>Web Remote</H1>");
  if (strcmp(params, "?cmd=on") == 0)
  {
    digitalWrite(outputPin, HIGH);
    e.print("<A HREF='?cmd=off'>Turn off</A>");
  }
  else if (strcmp(params, "?cmd=off") == 0) // Modified -- 2011 12 15 # Ben Schueler
  {
    digitalWrite(outputPin, LOW);
    e.print("<A HREF='?cmd=on'>Turn on</A>");
  }
  e.respond();
}
