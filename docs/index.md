---
permalink: /
---

# 3BC Language

<section class="row">
<div class="col s12 m6" markdown="1">

![3BC LANGUAGE LOGO ><](/images/3bc-logo-mid.png)

</div>
<div class="col s12 m6" markdown="1">

## Download last version!

{% assign release = site.github.releases | first %}

 * **Released:** {{ release.name }}
 * **Date published:** {{ release.created_at | date_to_long_string }}
 * **More:** [Changelogs](extra/changelogs) or [Download others versions](download).


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

* **[Tutorial :us:](guide/tutorial-en-us)**
* **[Tutorial :brazil:](guide/tutorial-pt-br)**
* **[Cheatsheet](guide/cheatsheet)**
* **[Source code]({{ site.github.clone_url }})**
* **[Platform Support](support)**
* **[Ambient Roadmap](extra/roadmap)**
* **[List of early developers](extra/early-adopters)**

</div>
<div class="col s12 m6 pull-m6" markdown="1">

## About ##

Low level language, tiny virtual machine that works on computers and microcontrollers. (Friendly Punched cards)

-------------------------------------------

Linguagem de baixo nível, pequena maquina virtual que funciona em computadores e microcontroladores. (Legível em cartões perfurados)

</div>
</section>
