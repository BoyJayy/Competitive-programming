// author: bjcb
/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣾⡟⣯⣽⣻⣿⣿⣿⣷⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣀⣴⣿⢻⣿⣿⢻⣿⣷⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣀⣴⣿⣿⣏⣿⣿⣿⡈⢻⣽⣿⣿⣾⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⢀⣴⣿⣿⣿⣿⢾⣿⣿⣿⣇⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢀⣴⠿⠿⠿⢿⣿⣿⣿⣿⣿⢻⢻⣄⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠷⠄⠀⠀⠀⠀⠀⠀⠀⠀
⠉⠀⠀⠀⠀⢸⣿⣿⣿⣿⢹⣒⠢⣿⣄⠀⠀⠚⢻⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣿⡏⣿⣿⡟⣿⣿⡮⠈⠀⠀⠰⣿⣿⠻⣿⣿⣧⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣿⣿⣼⣿⣇⠉⠋⠀⠀⡀⠀⠀⠉⠉⢀⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣄⠀⠀⢀⣉⡀⠀⠀⣠⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣷⡦⣀⣀⣀⢴⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣸⠿⢿⣿⣿⠛⠉⠀⠀⠀⠀⠀⠙⠛⢿⣿⡿⠿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢀⠎⠀⠀⣎⣿⣿⡂⠒⠒⢢⣤⣖⣛⣉⣁⣼⣿⡇⠀⠈⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣼⢀⠀⠀⠇⢹⣿⡍⡉⣹⣿⣧⠀⠀⠀⠀⣾⣿⣇⢀⠀⢰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢿⠀⢧⣀⡇⠘⣿⡇⠀⠉⢹⣧⡀⠀⠁⠈⣿⡿⢹⠎⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢸⠀⠀⢻⢆⠀⢿⡇⠀⠀⢸⡇⠻⣆⠀⢰⣿⠃⣺⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⡄⠀⢸⡄⠃⡈⣿⡀⠀⢨⢸⡦⢻⣧⣽⠿⢰⢿⠀⠀⢸⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⡅⠀⠸⡛⡄⠈⠹⠁⠀⢸⠈⣧⠀⠹⣏⢠⠇⢸⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢁⠀⠀⡇⠹⣥⠀⢡⠀⢸⠀⢸⡆⠀⢹⡟⠀⢸⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢰⠀⠀⣿⠀⠈⠄⠀⢡⠀⠀⠀⣧⠀⠀⢻⠀⢸⠀⠀⢸⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠈⡄⠀⣿⠀⠀⢠⠀⠀⢣⡄⠀⢽⠀⠀⢉⣧⣿⠀⠀⣼⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢇⠀⣿⠀⠀⠀⠄⠀⠀⠃⠂⢸⡇⠠⠃⢛⣿⠀⠀⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢸⢠⣿⠀⠀⠀⠀⠀⠀⠈⢢⡘⠃⠀⢰⠈⣿⠶⠒⠿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠈⠿⠘⠀⠀⠀⠀⡄⠀⠀⠈⠋⠢⠄⠈⢆⢻⠀⠀⠐⢌⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠃⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠈⠁⠈⢻⣦⡭⣍⠢⣽⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⢻⠹⣦⣷⣽⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣷⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⡄⠀⢰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⡆⠀⠘⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⠀⠀⠀⠸⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢸⠁⠀⢠⡇⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀⠀⠀⠀⢣⠀⠀⠀⢿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢸⠀⠀⠘⣼⠀⠀⠀⡄⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⢃⠀⠀⢸⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣿⠀⠀⠀⠘⡆⠀⠀⠰⠀⠀⠀⠀⠈⡄⠀⠀⠀⠀⠈⡆⠀⠀⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⡟⠀⠀⠀⠀⢡⠀⠀⠀⢃⠀⠀⠀⠀⢣⠀⠀⠀⠀⠀⠘⡄⠀⢸⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀
⠀⠀⠀⠀⡇⠀⠀⠀⠀⠈⡄⠀⠀⠀⢆⠀⠀⠀⠘⡀⠀⠀⠀⠀⠀⢹⠀⠀⢿⣿⣿⣿⣿⡄⠀⠀⠀⠀
⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠘⠀⠀⠀⠈⢂⠀⠀⠀⢃⠀⠀⠀⠀⠀⠀⣇⢸⠘⣿⣿⣿⣿⣇⠀⠀⠀⠀
⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣤⠀⠀⠀⠀⠀⠘⡆⡆⢹⣿⣿⣿⣿⠀⠀⠀⠀
⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠠⢱⣷⠘⣿⣿⣿⣿⡇⠀⠀⠀
⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⠀⠀⠀⠀⠀⠀⠈⠀⢀⢹⣿⣿⣿⣿⠀⠀⠀
⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠨⡄⠀⠀⠀⠀⠀⠀⠀⢐⣿⣿⣿⣿⣿⡆⠀⠀
⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⢀⠀⠀⢸⣿⣿⣿⣿⡇⠀⠀
⠀⠀⠀⠀⠣⠀⡀⠀⡀⠀⠀⠀⠀⣀⡀⣀⣀⣀⣀⣀⣀⣀⣆⣀⣠⣈⣴⣧⣿⣿⣿⣾⣿⡇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢿⠉⠉⠉⠉⠁⠉⡍⠀⠈⡇⠀⠀⠀⠀⠀⠀⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠸⡙⠶⢄⣀⠀⠀⢣⠀⠀⡇⠀⠀⠀⠀⠀⢸⠃⣿⣿⣿⣾⣿⣿⣿⣿⣿⣇⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠇⠀⠀⠀⠈⠉⢹⠀⠀⡇⠒⠂⠐⠒⠉⢸⢹⣿⣿⣿⣾⢿⣿⣿⣿⣿⣿⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠈⡆⠀⡇⠀⠀⠀⠀⠀⢸⢸⣿⣿⣿⣯⣿⣿⣿⣿⣿⣿⡄⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡄⠀⠀⠀⠀⠀⡇⠀⠃⠀⠀⠀⠀⠀⡞⠈⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⡇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⣷⠀⢠⠀⠀⠀⠀⠀⡇⠀⢸⣿⣿⣯⣷⣿⣿⣿⣿⣿⡇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢸⠀⠀⠀⢠⢿⠀⢸⢠⠀⠀⠀⡖⡇⠀⠀⢿⣿⣿⣿⣿⣿⣿⡟⢻⣿⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠞⠀⡖⠀⡎⣸⠀⠸⠀⠇⠀⢀⠁⢃⠀⠀⠘⣿⣿⣿⣿⣿⣿⡧⢸⣿⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡘⠀⠀⡇⠀⡇⢸⠀⠀⡃⠀⡇⢸⠀⢸⠀⠀⠀⢹⣿⣿⣿⣿⣿⡗⠨⣿⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡅⠀⠀⢸⠀⠀⢸⠀⠀⠀⠀⡇⠈⠀⠀⡇⠀⠀⠀⢿⣿⣿⣿⣿⡏⠀⣿⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠘⠀⠀⡇⠀⠀⢰⠀⢡⠀⠀⠀⢃⠀⠀⠀⠘⣿⣿⣿⣿⠇⠀⢿⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⡄⠀⡇⠀⠀⢰⠀⠈⠀⠀⠀⢸⠀⠀⠀⠀⢸⣿⣿⡟⠀⠀⢸⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⡇⠀⡇⠀⠀⠸⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⢸⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⢃⢠⠃⠀⠀⠀⡇⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢸⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⠀⠀⠀⢈⢰⠀⠀⠀⠀⢱⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⣿⡏⠀⠀⠀⢸⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⢸⠀⠀⠀⠀⠘⡄⠀⠀⠀⢸⠀⠀⠀⠀⠀⡟⠀⠀⠀⠀⢸⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⡇⢀⠀⠀⢸⠀⠀⠀⠀⢰⠃⠀⠀⠀⠀⣿⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⠀⢸⠀⠀⠀⠀⠀⠸⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠇⠀⠀⠀⢸⠀⠀⠀⠀⠀⢸⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠁⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⡆⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠞⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠰⡆⠀⠀⠀⠀⠀⡇⠀⠀⢠⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠀⠀⠀⡇⠀⠀⠀⠀⢀⠇⣀⠀⢀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠇⠀⠀⠀⢳⠀⠀⠀⠀⢸⡇⢁⣀⢹⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠰⢸⠀⠀⠀⠀⢠⣷⠿⠛⢿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⢀⣤⣤⣄⡇⠀⠀⠀⢠⠏⠀⠀⠈⢻⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡟⠉⠀⠛⡏⠀⠀⠀⣘⣀⡤⡤⠤⢄⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡄⠀⠀⠀⢣⡀⠀⠀⣿⠓⠛⠉⠉⠉⠚⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣶⠾⠿⠿⠿⢧⡀⠀⣿⣄⢼⣰⡴⣦⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣏⠠⡐⢄⢢⡰⣆⣴⠀⠀⠉⠛⠛⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠙⠛⠛⠒⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀*/
#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")
#pragma comment(linker, "/STACK:367772160")
using namespace std;
#define all(a) (a).begin(), (a).end()
#define endl "\n"
#define vec vector
#define pii pair<int, int>
#define se second
#define fi first
#define pb push_back
#define maxel(v) *max_element(v.begin(), v.end())
#define minel(v) *min_element(v.begin(), v.end())
#define yes cout << "YES\n";
//#define m1 cout << "-1\n";
#define no cout << "NO\n";
//using i128 = __int128;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll mod2 = 1e9 + 9;
const ll mod3 = 998244353;
const double pi = 3.141592653589793238;
const long double EPS = 1e-9;
#define DEBUG 1
#if DEBUG
#define del cout << '\n'
#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
template <class X, class Y>
ostream& operator<<(ostream& os, pair<X, Y> const& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template <class Ch, class Tr, class Container>
basic_ostream<Ch, Tr>& operator<<(basic_ostream<Ch, Tr>& os, Container const& x) {
    int i = 0, n = (int)distance(x.begin(), x.end());
    os << "{ ";
    for (const auto& y : x) os << y << (++i < n ? ", " : "");
    return os << " }";
}
template <typename... Args>
void _debug(const char* s, Args&&... args) {
    cout << "{ ";
    size_t i = 0, cnt = 0, n = sizeof...(args);
    auto next = [&]() {
        while (s[i] && (s[i] == ' ' || s[i] == ',')) ++i;
        size_t st = i;
        while (s[i] && s[i] != ',') ++i;
        return string(s + st, i - st);
    };
    auto dummy = {(cout << next() << ": " << args << (++cnt < n ? ", " : ""), 0)...};
    (void)dummy;
    cout << " }" << '\n';
}
#else
#define del
#define debug(...)
#endif
template <typename T>
ostream& operator<< (ostream &os, const pair<T, T>& a){
    return os << a.fi << " " << a.se;
}
template <typename T>
istream& operator>> (istream& in, pair<T, T>& a){
    in >> a.fi >> a.se;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, const vector<T>& a){
    for (int x : a) os << x << " ";
    return os;

}
template <typename T>
istream& operator>> (istream& in, vector<pair<T, T>>& a){
    for (pair<int, int>& x : a) in >> x.fi >> x.se;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, const vector<pair<T, T>>& a){
    for (pair<int, int> x : a) os << x.fi << " " << x.se << endl;
    return os;

}
template <typename T>
istream& operator>> (istream& in, vector<T>& a){
    for (int& x : a) in >> x;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, const set<T>& a){
    for (int x : a) os << x << " ";
    return os;
}
template <typename T>
ostream& operator<< (ostream &os, const map<T, T>& a){
    for (pair<int, int> x : a) os << x.fi << " " << x.se << endl;
    return os;
}
template <typename T>
void printrb(vector<T>* rb, int n) {
    for (int u = 0; u < n; ++u) {
        for (const T& v : rb[u]) {
            cout << u << " -> " << v << '\n';
        }
    }
}
template <typename T>
void print2d(const vec<vec<T>> &vec2) {
    for (const auto &row : vec2) {
        for (const auto &i : row) {
            cout << i << " ";
        }
        cout << endl;
    }
}
const int maxn = 3005;
int n;
vec<int> g[maxn];
int szv[maxn];
ll dp[maxn][maxn];
ll fact[maxn], ifact[maxn];

ll pw(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % mod3;
        a = a * a % mod3;
        e >>= 1;
    }
    return r;
}
ll C(int N, int K) {
    if (K < 0 || K > N) return 0;
    return fact[N] * ifact[K] % mod3 * ifact[N - K] % mod3;
}
void dfs1(int v, int p) {
    szv[v] = 1;
    vec<ll> from(1);
    from[0] = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs1(to, v);
        int a = szv[v];
        int b = szv[to];
        vec<ll> nxt(a + b);
        vec<ll> pref(b + 1);
        pref[0] = 0;
        for (int i = 0; i < b; i++) {
            pref[i + 1] = (pref[i] + dp[to][i]) % mod3;
        }
        for (int x = 0; x < a; x++) {
            for (int y = 0; y < b; y++) {
                ll ways = C(x + y, x);
                ways = ways * C(a + b - (1 + x + y), a - (1 + x)) % mod3;
                ways = ways * from[x] % mod3;
                ll s = (pref[b] - pref[y] + mod3) % mod3;
                nxt[x + y] = (nxt[x + y] + ways * s) % mod3;
            }
        }
        szv[v] += szv[to];
        from.assign(szv[v], 0);
        for (int i = 0; i < szv[v]; i++) from[i] = nxt[i];
    }
    for (int i = 0; i < szv[v]; i++) dp[v][i] = from[szv[v] - 1 - i];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod3;
    ifact[n] = pw(fact[n], mod3 - 2);
    for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i % mod3;
    dfs1(1, 0);
    ll ans = 0;
    for (int i = 0; i < n; i++) ans = (ans + dp[1][i]) % mod3;
    ans = ans * 2 % mod3;
    cout << ans << endl;
}
