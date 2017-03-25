<span>
[[ 
    $tags = explode(' ', $question->getTags());
    if ($tags[0]) {
        echo "Tags:";
    }
    foreach($tags as $tag) : 
]] 
    <a href="@@tag/view_questions/{{ $tag }}@@">{{ $tag }}</a>
[[  endforeach; ]]
</span>