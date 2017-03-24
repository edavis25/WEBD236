<span>
[[ 
    $tags = explode(' ', $question->getTags());
    if ($tags[0]) {
        echo "Tags:";
    }
    else {
        echo "Tags: <i>none</i>";
    }

    foreach($tags as $tag) : 
]]
    
<a href="@@tag/view_questions/{{ $tag }}@@">{{ $tag }}</a>
    
[[  endforeach; ]]
</span>