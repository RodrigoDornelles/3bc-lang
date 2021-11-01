---
title: Download
description: See all changelogs and download the latest version of 3BC language.
click_here: https://3bc-lang.org/download
redirect_from: ['changelogs', 'docs/changelogs', 'extra/changelogs']
---

{% assign first_release = site.github.releases | first %}
{% for release in site.github.releases %}

{{ release.name }}
------------------

<details markdown="1">
<summary>Changelogs</summary>

{{ release.body }}

</details>

{% if first_release.tag_name != release.tag_name %}
<details markdown="1">
<summary>Download</summary>
{% else %}
<br/>
{% endif %}

<section class="row">
{% for asset in release.assets %}
<div class="col s12 m6">
    <a href="{{ asset.browser_download_url }}"
        class="btn btn-large btn-block" download>
        <span>{{ asset.name }}</span>&nbsp;
        <span>{{ asset.size | divided_by: 1024 }} KB<i class="material-icons">file_download</i></span>
    </a><br/>
</div>
{% endfor %}
</section>

{% if first_release.tag_name != release.tag_name %}
</details>
{% endif %}
<br/><br/>

{% endfor %}