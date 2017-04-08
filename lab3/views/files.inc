<div id="attachments">
    [[ foreach ($files as $file) : ]]
        <a href="@@file/view/{{$file->getId()}}@@">View</a>&nbsp;{{$file->getOrigName()}}
    [[ endforeach; ]]
</div>