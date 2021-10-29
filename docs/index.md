---
permalink: /
---

# 3BC Language

{% assign release = site.github.releases | first %}

<section class="row">
<div class="col s12 m6" markdown="1">

![3BC LANGUAGE LOGO ><](/images/logo-3bc-mid.png)

</div>
<div class="col s12 m6" markdown="1">

## Download last version!

 * **Released:** {{ release.name }}
 * **Date published:** {{ release.created_at | date_to_long_string }}
 * **More:** [Changelogs](docs/changelog) or [Download others versions](docs/download).


<div class="row">
{% for main in site.data.main_plataforms %}
{% assign asset = release.assets | where: "name",  main.name | first %}

<div class="col s12 m4">
{% include btn_download.rhtml title=main.title %}
</div>

{% endfor %}
</div>
</div>
</section>

<section class="row">
<div class="col s12 m6 push-m6" markdown="1">

## Documentation ##

* **[Tutorial :us:](docs/tutorial-en-us)**
* **[Tutorial :brazil:](docs/tutorial-pt-br)**
* **[Cheatsheet](docs/cheatsheet)**
* **[Platform Support](docs/support)**
* **[Ambient Roadmap](#ambient-roadmap)**
* **[List of early developers](#list-of-early-developers)**

</div>
<div class="col s12 m6 pull-m6" markdown="1">

## About ##

Low level language, tiny virtual machine that works on computers and microcontrollers. (Friendly Punched cards)

-------------------------------------------

Linguagem de baixo nível, pequena maquina virtual que funciona em computadores e microcontroladores. (Legível em cartões perfurados)

</div>
</section>
