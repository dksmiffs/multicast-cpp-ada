with Ada.Text_IO; use Ada.Text_IO;
with Interfaces.C.Strings;


procedure Rcv_Ada is
  function Read_From_The_Sock return Interfaces.C.Strings.chars_ptr
    with Import => True, Convention => C, External_Name => "read_from_the_sock";
  cstr : Interfaces.C.Strings.chars_ptr := Read_From_The_Sock;
begin
  Put("From Ada ==> ");
  Put_Line(Interfaces.C.Strings.Value(cstr));
end Rcv_Ada;
