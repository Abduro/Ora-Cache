::To remove files/folders from the repository on github.com
(1) To delete a file from both GitHub and your local computer:
    git rm filename.txt
    git commit -m "Remove filename.txt"
    git push origin main

(2) To delete a file from GitHub but keep it safely on your local computer:
    git rm --cached filename.txt
    git commit -m "Remove filename.txt from remote"
    git push origin main

(3) To delete an entire folder:
    git rm -r folder_name
    git commit -m "Remove folder_name"
    git push origin main

To automatically close the console when debugging stops, enable:
Tools->Options->Debugging->Automatically close the console when debugging stops.

VS *BUGS*
(1) When adding new project to the solution file manually, do *not* put whitespace before comma sign;
... Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "ebo_test_$$t.case.draw",  ... it is correct;
... Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "ebo_test_$$t.case.draw" , ... the whitespace before of the comma leads to:

The selected file is a solution file, but appears to be corrupted and cannot be open.