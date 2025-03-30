
(1) These classes, especially in project win.popup, use heavily message handling macros that is defined in ATL;
(2) Regarding using 'this' keyword: it is very important to use 'this' for explicit referencing to field or attribute of a particular class object,
    otherwise security check program will throw an error, for example, when the code is used in banking informational system;