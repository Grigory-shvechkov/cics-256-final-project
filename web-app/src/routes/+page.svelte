<script lang="ts">
    import { Button } from "$lib/components/ui/button";
    import ChevronUp from "@lucide/svelte/icons/chevron-up";

    async function handleForwardClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/forward", {
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

    async function handleForwardStopClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/forward?stop=true", {
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

    async function handleBackwardClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/backward", {
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

    async function handleBackwardStopClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/backward?stop=true", {
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
        <Button onclick={handleForwardStopClick} size="icon">
            STOP FORWARD
        </Button>
        <Button onclick={handleBackwardClick} size="icon">
            <ChevronUp class="rotate-180" />
        </Button>
        <Button onclick={handleBackwardStopClick} size="icon">
            STOP BACKWARD
        </Button>
    </div>
</div>
