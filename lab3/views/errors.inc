<div id="errors">
    [[ if (isset($errors) && count($errors) > 0) : ]]
        <ul>
            [[ foreach($errors as $error) : ]]
                <li>{{ $error }}</li>
            [[ endforeach; ]]
        </ul>
    [[ endif; ]]
</div>