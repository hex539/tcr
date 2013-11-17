\documentclass[a4paper,8pt]{article}
  \usepackage[
    bookmarks,
    colorlinks=false,
    pdftitle={Team Contest Reference},
    pdfauthor={Robin Lee; James Stanley; Nikolay Yordanov},
    pdfsubject={Programming contest shortcuts},
    pdfborder={0 0 0}
  ]{hyperref}

  \usepackage{makeidx}
  \usepackage{amsmath}
  \usepackage{listings}
  \usepackage{courier}
  \usepackage{euler}
  \usepackage{color}
  \usepackage{parskip}
  \usepackage{fancyhdr}
  \usepackage[toc]{multitoc}

  \usepackage{pstricks}
  \usepackage{pstricks-add}
  \usepackage{graphicx}

  \usepackage[top=1.5cm,bottom=0.75cm,left=0.75cm,right=0.75cm]{geometry}
    \setlength{\columnsep}{.5cm}
    \setlength{\columnseprule}{.01cm}

  \pagestyle{fancy}
    \renewcommand{\headrulewidth}{0pt}
    \lhead{Bath University}
    \rhead{Page \thepage}
    \cfoot{}

  \begin{document}
    \definecolor{black}{rgb}{0.0, 0.0, 0.0} 
    \definecolor{bland}{rgb}{0.3, 0.3, 0.3} 
    \definecolor{white}{rgb}{1.0, 1.0, 1.0} 

    \lstset{
      extendedchars=false,
      inputencoding=utf8,
      language=C++,
      basicstyle=\footnotesize\ttfamily,
      backgroundcolor=\color{white},
      commentstyle=\color{bland},
      showstringspaces=true,
      showtabs=false,
      tabsize=2,
      captionpos=t,
      breaklines=true,
      breakatwhitespace=false,
      escapechar={¬}
    }

    \begin{titlepage}
      \begin{center}
        \includegraphics[height=2.56cm,clip]{bath.png}

        \large{Team Contest Reference}

        \rule{10cm}{0.1mm}
      \end{center}

      \setcounter{tocdepth}{4}
      % \begin{small}
        \tableofcontents
      % \end{small}
    \end{titlepage}

