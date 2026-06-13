---
name: complexity-cleanup
description: "Use when reducing cognitive or cyclomatic complexity, interpreting complexity reports, simplifying high-complexity symbols, or planning cleanup that should avoid mechanical helper extraction."
---

# Complexity Cleanup

## Purpose

Complexity is measured pressure from branching, nesting, state transitions, and mixed responsibilities inside a code symbol. A complex symbol is a function, method, component, or module member whose essential problem is that one named unit now makes too many decisions, coordinates too many effects, or represents too many domain concepts at once. Good cleanup reduces the real cause of that pressure while preserving observable behavior.

Do not treat a high complexity score as an instruction to split code into smaller private helpers. A score is a smoke signal. The cleanup target is the underlying shape of the work.

## First Pass

1. Run the local complexity command when one exists, such as `npm run complexity`.
2. Identify the highest-offending symbols, their files, and whether the reported score is cognitive complexity, cyclomatic complexity, or both.
3. Use compiler-aware code navigation when available, such as `scip-query`, to inspect references, callers, callees, and ownership before editing.
4. Read the surrounding tests, routes, workflows, composables, stores, and components that define current behavior.
5. Capture the behavior contract in plain language before proposing a new shape.

## Classify The Cause

Classify the symbol before refactoring. Most complex symbols are one of these:

- Policy matrix: many rules choose an allowed action, status, entitlement, visibility, or validation result.
- Orchestration routine: one function sequences loading, permission checks, requests, mutation, toasts, navigation, and refreshes.
- State machine: many branches represent lifecycle transitions across statuses or modes.
- Data shaping pipeline: one symbol normalizes, filters, groups, sorts, paginates, serializes, and formats records.
- UI owner overload: one component owns fetching, form state, derived domain state, action handlers, and rendering.
- Boundary overload: validation, permission, error translation, logging, and persistence are mixed in the same route or adapter.
- Algorithmic parser: nested control flow exists because the code is walking syntax, tokens, graphs, or structured input.

If none of these fit, name the real-world work the code is doing and why that work produces branches.

## Choose The Better Shape

Prefer a shape that makes the domain concept explicit:

- For policy matrices, create a pure policy resolver, rule table, or decision model that returns a named result. Keep effects outside it.
- For orchestration routines, keep a thin orchestration shell and move stable decisions into pure functions or workflow modules.
- For state machines, model states and transitions explicitly instead of scattering `if` chains across handlers.
- For data shaping, separate query/load parameters, filtering, sorting, pagination, grouping, and display formatting.
- For UI overload, split server-state loading, local form state, domain derivation, command handlers, and presentational rendering only at real boundaries.
- For route or adapter overload, move business rules into workflows and keep validation, permissions, persistence, error translation, and logging on the standard project path.
- For algorithmic parsers, use a clearer traversal object, visitor, table-driven parser, or named phases rather than arbitrary helper shards.

Good cleanup often changes data shape, control-flow ownership, or module boundaries. It does not merely hide branches behind names.

## Tests And Safety

Before risky edits, add characterization tests around the current externally visible behavior. A characterization test is a test whose essential job is to pin down what the system currently does before changing its implementation.

Keep changes in small slices:

- Establish baseline complexity and behavior.
- Extract or model one real concept.
- Run focused tests.
- Run the complexity report again.
- Compare the new shape to the old contract.

If the score improves but the code is harder to understand, the cleanup failed. If the score stays similar but responsibilities become explicit and easier to test, document why that is still a good cleanup.

## Anti-Patterns

- Do not split a function into many same-file helpers that share the same temporary variables and mental state.
- Do not introduce an abstraction unless it names a real concept, removes meaningful duplication, or creates a testable boundary.
- Do not move domain rules into generic utilities.
- Do not flatten branches by hiding them in clever data structures that future maintainers cannot read.
- Do not combine unrelated cases just because they share a syntax shape.
- Do not change behavior to satisfy a metric unless the user explicitly approves that product change.

## Completion Standard

Report the before and after complexity numbers when available, the behavioral tests or checks run, and the new conceptual shape. Name any remaining high-complexity symbols that should be handled in a later slice.
