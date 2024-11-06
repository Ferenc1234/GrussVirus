# GrussVirus

This app will change your typed text "Windows" to "Linux" (Just what Grussmann love)

## How to run the app

1. Download or copy `main.c` to your computer and save it somewhere

2. Run this command in windows powershell inside the folder with the file (make sure you have gcc installed) <br>
`gcc main.c -o linux.exe -s`<br>
or use <br>
`gcc main.c -o linux.exe -s -mwindows`<br>
for hidden window (you probably want the second option).

3. Double click the compiled file (linux.exe) 
4. Enjoy!

## Making the app run automatically after windows startup

1. Press `Ctrl + R` to open RUN window
2. Write `shell:Common Startup` into the opened window
3. Press OK
4. Now move or copy the linux.exe file into the opened folder (you will need admin acces probably)
5. Your app should start after startup of your machine!

