%% views/header.inc %%

<h1>{{ $title }}</h1>
    [[ foreach($groups as $group) :  ]]
    <table style="border: 1px solid black; border-collapse: collapse">
        <tr><th colspan="3">{{ $group -> getName() }}</th></tr>
        <tr style="border: 1px solid black;">
            <td style="border: 1px solid black; padding: 5px"><a href=""> Members </a></td>
            <td style="border: 1px solid black; padding: 5px"><a href=""> Permissions </a></td>
            <td style="border: 1px solid black; padding: 5px"><a href=""> Delete </a></td>
        </tr>
    </table>
    <br />
    [[ endforeach; ]]
    

%% views/footer.inc %%
