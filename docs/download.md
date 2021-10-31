---
title: Download
description: Get the last version of 3BC Language now!
click_here: https://3bc-lang.org/docs/download
---

{% assign release = site.github.releases | first %}

<section class="row">

<div class="col s12 m6" markdown="1">

![3BC LANGUAGE LOGO ><](/images/logo-3bc-mid.png)

</div>

<div class="col s12 m6" markdown="1">

## Download last version!

 * **Version:** {{ release.name }}
 * **Date published:** {{ release.created_at | date_to_long_string }}
 * **For more details:** [click here!]({{ '/docs/changelogs' | relative_url | append: '#' | append: release.name }})
  
</div>

</section>

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
