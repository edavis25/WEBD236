%% views/header.inc %%

<h1>{{$title}}</h1>
<p>
    The following orphaned files have been removed from:<br />
    <b>{{$directory}}</b>
</p>
<p><i>Note: This information has also been logged.</i></p>
<hr /><br />
<table class="users-table">
    <tr>
        <th>{{$numberRemoved}} Files Removed:</th>
    </tr>
    [[ foreach($orphans as $orphan) : ]]
        <tr>
            <td>{{$orphan}}</td>
        </tr>
    [[ endforeach; ]]
</table>

<br />
<a href="@@admin@@">&lt;&lt; Back</a>
%% views/footer.inc %%
