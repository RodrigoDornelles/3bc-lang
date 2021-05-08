---
title: Changelogs
description: See all changelogs and download the latest version of 3BC language.
---

<!-- SHOW ON GITHUB {% if false %}-->

 * click here: <https://github.com/RodrigoDornelles/3bc-lang/releases>

<!-- SHOW ON GITHUB {% endif %}-->

<!-- HIDE ON GITHUB {{ '--' | append: '>' }}
{% for release in site.github.releases %}

{{ release.body }}

{% for asset in release.assets %}
<a href="{{ asset.browser_download_url }}" class="btn" download>
    <span>{{ asset.name }}</span>&nbsp;
    <span>{{ asset.size | divided_by: 1024 }} KB<i class="material-icons">file_download</i></span>
</a>
{% endfor %}

{% endfor %}
<!--  HIDE ON GITHUB -->