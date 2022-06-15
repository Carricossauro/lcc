export default function Main() {
  const redirect = (page) => {
    window.location.href = page;
  };
  return (
    <div className="m-auto h-screen flex justify-center items-center justify-evenly">
      <button className="flex items-center justify-center h-14 w-56 rounded-3xl cursor-pointer bg-color1 text-2xl hover:text-white duration-500">
        My Games
      </button>
      <button
        className="flex items-center justify-center h-14 w-56 rounded-3xl cursor-pointer bg-color1 text-2xl hover:text-white duration-500"
        onClick={() => redirect("/Author/Edit")}
      >
        Create
      </button>
      <button className="flex items-center justify-center h-14 w-56 rounded-3xl cursor-pointer bg-color1 text-2xl hover:text-white duration-500">
        Explore All
      </button>
    </div>
  );
}
