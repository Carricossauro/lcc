module.exports = {
    content: ["./src/**/*.{html,js}"],
    theme: {
        extend: {
            colors: {
                color1: "#0fa3b1",
                color2: "#d9e5d6",
                color3: "#eddea4",
                color4: "#f7a072",
                color5: "#ff9b42",
            },
            backgroundImage: {
                "split-color2-white":
                    "linear-gradient(to bottom,  #d9e5d6 50%, white 50%);",
                about: "url('../src/assets/about.png')",
            },
        },
    },
    plugins: [],
};
