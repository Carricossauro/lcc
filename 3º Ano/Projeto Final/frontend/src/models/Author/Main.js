export default function Main() {
  const redirect = (page) => {
    window.location.href = page;
  };
  return (
    <div className="m-auto h-screen flex flex-col sm:flex-row justify-center items-center sm:justify-evenly">
      <button
        className="flex items-center justify-center h-14 w-56 rounded-3xl cursor-pointer bg-color1 text-2xl hover:text-white duration-500 my-5 sm:my-0"
        onClick={() => redirect("/Author/Mygames")}
      >
        My Games
      </button>
      <button
        className="flex items-center justify-center h-14 w-56 rounded-3xl cursor-pointer bg-color1 text-2xl hover:text-white duration-500 my-5 sm:my-0"
        onClick={() => redirect("/Author/Create")}
      >
        Create
      </button>
      <button
        className="flex items-center justify-center h-14 w-56 rounded-3xl cursor-pointer bg-color1 text-2xl hover:text-white duration-500 my-5 sm:my-0"
        onClick={() => redirect("/Author/Explore")}
      >
        Explore All
      </button>
    </div>
  );
}
