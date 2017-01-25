<?php
/*
echo "VIEW QUESTION! <br />";

foreach ($question as $row)
{
	echo "$row <br />";
}

echo $question['Date'];
*/
?>


%% views/header.inc %%

<h1>{{$question['Title']}}</h1>
<p>Posted on: {{$question['Date']}}</p>
<p>Tags: {{$question['Tags']}}</p>
<p>{{$question['Content']}}</p>

<a href="">[Edit]</a>
<a href="">[Delete]</a>
<br /><br />
<a href="@@index@@">&lt;&lt; Back</a>
