<a id="readme-top"></a>

[![Issues][issues-shield]][[issues-url](https://github.com/RCarScar/SpellcastRemastered/issues)]
[![LinkedIn][linkedin-shield]][[linkedin-url](https://www.linkedin.com/in/ryan-chen-3565aa357/)]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/RCarScar/SpellcastRemastered">
    <img src="images/Disc.png" alt="Logo" width="160" height="160">
  </a>

<h3 align="center">Spellcast Solver</h3>


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

Here's a blank template to get started. To avoid retyping too much info, do a search and replace with your text editor for the following: `github_username`, `repo_name`, `twitter_handle`, `linkedin_username`, `email_client`, `email`, `project_title`, `project_description`, `project_license`

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![Next][Next.js]][Next-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ```

### Installation

1. Ensure you have jsonCPP or install using a package manager for CPP. I would recommend vcpkg and have even included it in the project for convenience and compatability.
2. Clone the repo
   ```sh
   git clone https://github.com/RCarScar/SpellcastRemastered.git
   ```
3. Install JSONCPP
   Search documentation for your manager's install method. VCPKG will be
   ```sh
   vcpkg install jsoncpp
   ```
   If you choose vcpkg, ensure you have ran the command below and restarted your project folder.
   ```sh
   vcpkg integrate install
   ```
5. Build or debug run the project in Visual Studio Code by running the project. VS Code will work but will require configuration.
6. Done! Enter the prompts asked by the program and exit to complete.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage
This is an application that will solve the Spellcast Discord Activity.

![image](https://github.com/user-attachments/assets/07e1e1f6-9808-48e6-bd6a-02be91d8c74e)
Ensure you install jsoncpp integration in either a manager or manually configured.

![image](https://github.com/user-attachments/assets/5c375ea3-cff2-461e-96f7-05149f8b73b0)
A simple prompt when ran correctly will appear as above.

![image](https://github.com/user-attachments/assets/22cb61ef-5959-478a-adc2-11638fbae1ed)
Given a 5 by 5 grid, we form words by connecting letters.

![image](https://github.com/user-attachments/assets/28683658-cbba-4852-bc21-47e214ec3cd3)
This program will calculate all possible words using asynchronous multithreading.

![image](https://github.com/user-attachments/assets/0216f4e8-4a4c-4ee7-bc32-dd3ec22f7060)
It will then spit out the longest words to the shortest words

![image](https://github.com/user-attachments/assets/808bf19d-eed2-4170-b182-62c879ce42af)
Given the objective is to win the game, I have added a "Swap" setting, as the current weakness of this program is that it doesn't account for the abilites. Swap being the most powerful ability other than reshuffling means that the user can swap a single letter with another to form a better word. The answers above show the result of every possible word having a singular letter swapped out as well as not swapped.


<!-- ROADMAP -->
## Roadmap

- [ ] Feature 1
- [ ] Feature 2
- [ ] Feature 3
    - [ ] Nested Feature

See the [open issues](https://github.com/github_username/repo_name/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. This is currently a solo project, and would benefit from further enhancement, whether speed, or user convenience.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Ryan Chen - Rchen158@ucsc.edu - [@Discord]fluffy12345

Project Link: [https://github.com/RChen158/SpellcastRemastered](https://github.com/RChen158/SpellcastRemastered)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[Next.js]: https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/1200px-ISO_C%2B%2B_Logo.svg.png
[Next-url]: https://isocpp.org
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
