workflow "on push, lint with cpplint" {
  resolves = ["GitHub Action for cpplint"]
  on = "push"
}

action "GitHub Action for cpplint" {
  uses = "cclauss/GitHub-Action-for-cpplint@master"
  args = "cpplint --recursive ."
}

workflow "on pull request, lint with clang-tidy " {
  on = "pull_request"
  resolves = ["clang-tidy"]
}

action "clang-tidy" {
  uses = "muxee/clang-tidy-action@master"
  secrets = ["GITHUB_TOKEN"]
  args = "-checks=*"
}
