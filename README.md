TarotBot
===========

An Artificial Intelligence for the Tarot game.


Requirements
-----------

- **Node.js** (v5.3.0) installed + in your PATH Environment Variable
- **Python** (v2.7.11) installed + in your PATH Environment Variable


Set-up
-----------

Install **Node-Gyp** using this command `npm install -g node-gyp`.  
Run the command `node-gyp configure` from the project root folder.

After the first configure, you will find a `TarotBot.vcxproj` file inside the `build` folder, which allows you to open the project with *Visual Studio*.


How to build
-----------

Each time you create a `.h` or a `.cpp` file, add it into the `sources` list of the `binding.gyp` file, then re-run the command `node-gyp configure` from the project root folder.

Run the command `node-gyp build` from the project root folder.


How to test
-----------

Set-up your test inside the `test.js` file, then run the command `node test` from the project root folder.
