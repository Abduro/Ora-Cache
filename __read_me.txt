To automatically close the console when debugging stops, enable:
Tools->Options->Debugging->Automatically close the console when debugging stops.

VS *BUGS*
(1) When adding new project to the solution file manually, do *not* put whitespace before comma sign;
... Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "ebo_test_$$t.case.draw",  ... it is correct;
... Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "ebo_test_$$t.case.draw" , ... the whitespace before of the comma leads to:

The selected file is a solution file, but appears to be corrupted and cannot be open.