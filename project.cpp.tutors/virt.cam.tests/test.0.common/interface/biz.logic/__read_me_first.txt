:: JavaScript files' brief description:

root.o.body.js    - this is common body javascript file, it contains common HTML elements' IDs declaration, and getting bounding rectangles;

root.0.rulers.js  - contains HTML canvases for drawing rulers and cross of active/selected HTML object position:
                    vertical ruler along left side of the browser window and horizontal ruler along bottom side of the window;

root.0.sidebar.js - this is javascript functions' file for HTML sidebar control; it is used for listing test cases' URLs on the main/home HTML page;

root.0.statusb.js - this is javascript functions' file related to HTML statusbar control;
root.0.utils.js   - common utilities that are used in other javascript functions;

test.0.common.js  - this test case event handler javascript functions' file;

::note: (1) all javascript files contain HTML elements' identifiers declaration, which are used for finding an element by its identifier;
        (2) the order in which javascript files must be included:
            root.0.utils.js     << must be included first;
            root.0.status.js    << must be included second;
            root.0.sidebar.js   << optional, is used by 'Home' page only;
            root.0.body.js      << contains common HTML elements IDs, and getting bounding rectangles of elements which are found by those IDs;
            root.0.rulers.js    << optional, can be used by any test case page, excluding 'Home' page; this file must include 'root.0.body.js';
            {test case file}.js << the last <script> node includes the specific javascript file which is used by test case HTML page;