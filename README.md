<a id="readme-top"></a>

[![LinkedIn][linkedin-shield]][linkedin-url]



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
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

I made this project to beat my friends at SpellCaster, it was also in my interest to learn graph theory, asynchronous multithreading, and operator overloading.

This program works by using a 5x5 grid, there were actually two attempts. One was overcomplicated and deprecated. The other attempt was a very simple and effective solution. SpellCast Solver is the one that works, SpellCast Remade was the less successful attempt.
After making it successfully, I implemented the asynchronous multithreading.

First, I started by importing JsonCPP to use operations on the program.

Then, I set up other required modules, I created the Node, Done, and WordList class. I also implemented operator overloading on ones necessary, such as DictionaryMetrics where you need to track words removed, and total word count.

The main program begins by removing all locked files, as ending the program abruptly may leave behind lock files from asynchronous threading. I never encountered issues with this, but put it in as it's something that happens commonly in other programs like Github and such.
Then, I have a main dictionary file with all known english words be split into n amount of files. By splitting the files, we are setting them up to be read by multi threads to easily access them after the cache.

Then, we check if the files have been cached, if they have then we do not need to cache them, meaning this will run very fast excluding the first time it's run. I had a program test speeds of the asynchronous threading, and 370 threads was the number I ended up landing on.
As the files are read, it locks the files so the threads don't accidentally read from the same file or write. While these files are only reading, I was inexperienced at the time and didn't want to deal with any issues regarding reading/writing. This also helps to exclude duplicate entries.

Then, we create the grid while the async runs in the background. As the input is just letters, we use a 2-D array. This is possibly an inefficiency and may be improved, but negligable compared to the word lookup time complexity.

We then hash all nodes in the grid, setting adjacent nodes diagonal, next to, above and below. In the final step, we just match dictionary words with the letters traversed so far. 
Throughout this process, we have a clock timing from start to finish, one for caching and one for runtime without cache.

Overall, the async version of this process is actually slower without including the cache time. I believe this is because the time reading and writing is larger than the time it takes to go through the dictionary, meaning asynchronous multithreading should either not be used here, or should be reimplemented to reduce read/write times.

To account for swapping, we simply have a single letter leeway, and so if a single letter doesn't match, it continues on as if it did match. This can be the beginning letter aswell. It also takes the letter from a pool of known letters to ensure swapping is indeed possible.

It's important to note that not all words in the english dictionary work in Spellcast, and there are fictional words in Spellcast that work, so data wrangling would be necessary to get a 100% success rate.



### Built With

* [[CPP.cpp]]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

You will have to build the project yourself to run it, below are prerequisites to running the spellcast solver.

### Prerequisites

VCPKG, JSONCPP
  ```sh
  vcpkg install jsoncpp
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



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. This is currently a solo project, and would benefit from further enhancement, whether speed, or user convenience.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Ryan Chen - Rchen158@ucsc.edu - [Discord-shield]fluffy12345

Project Link: [https://github.com/RChen158/SpellcastRemastered](https://github.com/RChen158/SpellcastRemastered)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/RCarScar/SpellcastRemastered/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/ryan-chen-3565aa357/
[CPP.cpp]: https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social
[Discord-shield]: https://static-00.iconduck.com/assets.00/discord-icon-256x256-9roejvqx.png
[CPP-url]: https://isocpp.org
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
