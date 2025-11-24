# Using VSCode to Connect to GitHub on Windows


This is my full workflow for connecting Visual Studio Code (VSCode) to GitHub on a **Windows development environment**.

## Prerequisites
Before starting, ensure you have the following:
- **Visual Studio Code (VSCode) [Download VS Code here](https://code.visualstudio.com/)**
- **Git for Windows (includes Git Bash) [Download Git here](https://git-scm.com/).**
- **A GitHub account**

## Steps to Connect to GitHub

1. **Install the GitHub Extension for VSCode**
    - Open VSCode.
    - Click the **Extensions** icon on the left sidebar.
    - Search for "GitHub Pull Requests and Issues" and install the extension.

2. **Sign in to GitHub**
    - Press `Ctrl + Shift + P` to open Command Palette.
    - Type `GitHub: Sign in` and select the option.
    - Follow the prompts to authenticate with your GitHub account.

3. **Configure Git on Windows**
**Set your Git global username and email (first‑time only):**
```bash
git config --global user.name "Your GitHub Name"
git config --global user.email "your_email@example.com"
```

4. **Clone a GitHub Repository**
    - Open Command Palette: `Ctrl + Shift + P`.
    - Search: `Git: Clone`.
    - Paste the repository URL
    - Choose a local folder
    - When VSCode asks to open the project → click **Open**.

5. **Make Changes and Commit**
    - Edit files in the repository as needed.
    - Go to the Source Control view in VSCode.
    - Stage your changes, write a commit message, and commit the changes.

6. **Push Changes to GitHub**
    - In the Source Control panel, click **Sync Changes** or **Push**.
    - This will push your changes to the GitHub repository.

## Additional Tips
- Use the built-in terminal in VSCode for advanced Git commands.
- Enable GitLens extension for enhanced Git insights.

By following these steps, you can easily connect and manage your GitHub repositories using Visual Studio Code.
