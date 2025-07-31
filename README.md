# Password Manager
This terminal application allows you to store your password locally. <br/>
For your data safety, this password manager uses **AES-128 CBC** for the encryptions and decryptions. <br/>
Then, for your data integrity, the application uses **hex** and **Base64** to prevent data loss across operating systems.
> For Windows devices, verify your compiler path in the **build.bat** script before compilation.

# 📦 Requirements
- CMake (**if you want to use the default build scripts**).
- OpenSSL.

# 📥 Installation
1) Download the project. <br/>
2) Compile it. <br/>
3) Enjoy! <br/>

# ⚙️ Compilation
The default compilation scripts (**build.sh** / **build.bat**) compile the entire project for you. Once the compilation is done, you can retrieve the executable at the following paths:
- `./build/win/out/pwd.exe` for Windows systems.
- `./build/linux/out/pwd` for Linux systems.

# ❔ How to use it
To use this software, you only need to run the executable, create a new account if you are running it for the first time, or simply log in if it's not. Then, you can freely create, show and remove passwords to your account!

# 🤝 User Agreement
By downloading and/or using this program, you confirm that you are solely responsible for how you use this software. You agree as well that this agreement extends to any prior version of the program, and any new version of the user agreement in any future update, overwrites this one.
