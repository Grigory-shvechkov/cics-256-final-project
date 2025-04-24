<script lang="ts">
    import { Button } from "$lib/components/ui/button";
    import ChevronUp from "@lucide/svelte/icons/chevron-up";

    async function handleForwardClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/rotate?leg=fl&joint=hip&angle=45", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
        console.log(response);
        if (response.ok) {
            const result = await response.json();
            console.log("Success: ", result);
        } else {
            console.log("Error: ", response);
        };
    };
</script>

<div class="flex flex-col items-center gap-8 p-8">
    <h1 class="text-center text-4xl font-semibold">Robot Spider Control</h1>
    <div class="flex flex-col">
        <Button onclick={handleForwardClick} size="icon">
            <ChevronUp />
        </Button>
    </div>
</div>
