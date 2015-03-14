I have added a C# project for the express purpose of prototyping and testing. I know C# is by no means cross-platform, but for our purposes it will work fine. The final, C++ version will indeed be cross platform, but we need to perfect our algorithm first. C# -> C++ is much easier than English -> C++.

I have also revolutionized the parser with conceptual help from WindowsDevPro, and I truly hope HE WILL ACTUALLY START CONTRIBUTING CONCRETELY :)

Instead of going character by character, we now 'tokenize' the string much the same way a compiler does. As we go through the string, we split it into Arg\_Part structs (a string value and a type). This is not only easier to understand, but will ultimately end up being faster design-time AND run-time. Too many loops are bad for the heart.

## UPDATE ##
The C# tokenizer is nearly complete! We still have an issue if there are two consecutive Groupers, but hopefully that will be an easy fix. Once that is taken care of, it will be an easy job to take an array of Param\_Args (a new, public struct taking one char and one double) and substituting such values.

IDEA: To add all the variable keys at once, just put them in a string and be like .c\_str(); /**so clever**/ in the constructor. The 'variable' arg will become an array of chars (instead of just one) to allow for multivariable equations. OR have the Param\_Args struct literally be a keyed array of char-double pairs... much thinking to do after class