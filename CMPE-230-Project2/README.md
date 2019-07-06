Some Assumptions:
- We assumed starting and ending semesters will be different in inputs.
- We assumed course codes without digits (like SFL) are undergraduate.
External Libraries:
- We used urllib.request, re(regexp module) and BeautifulSoup for handling requests from Web and
HTML.
Implementation:
- We wrote a geturl function that takes a semester and a department and return the urllib
using regular expressions
- We wrote a download_info function that takes an url and returns the necessary information about
courses as sets and dictionaries.
We used BeautifulSoup here to take necessary data from HTML tables.
- We embedded the department names and codes to our program with a list and a dictionary.
- We took the input string from console and parsed it to find start and end semesters, then created a list
that contains all semesters between
start and end semesters.
- For every semester and every department we called the download_info function, while doing this
we computed number of courses and instructors for every semester, put the course names for every
department codes
into firstblock dictionary, and put all the information to lastmission dictionary. We handle departments
that have two long names(like ASIA)
and the departments with a unique long name differently here.
- At the last stage, we iterate over all departments, computing their number of courses(grad and
undergrad) and distinct instructors by looking at firstblock
and lastmission dictionaries and print all the course information in CSV.
